#include <GL/glew.h>
#include <SDL.h>

#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <unordered_map>

#include "color.hpp"
#include "common.h"
#include "render/shader.hpp"
#include "state/machine.hpp"
#include "state/state.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

typedef float t_mat4x4[16];

float fps = 0;
Uint32 start_time, frame_time;

struct main_loop_data_t {
  StateMachine& m;
};

typedef enum t_attrib_id { attrib_position, attrib_color } t_attrib_id;

void main_loop(void* d) {
  main_loop_data_t* data = reinterpret_cast<main_loop_data_t*>(d);
  frame_time = SDL_GetTicks() - start_time;
  start_time = SDL_GetTicks();
  fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
  data->m.handleEvents();
  data->m.update();
  // data->m.render(&data->m.ctx);
}

int main() {
  const int width = 1024;
  const int height = 768;
  srand(time(NULL));

  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window* window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, width, height,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  StateMachine machine;

  glewInit();

  GLuint program = LoadShaders("shaders/vertex_shader.vertexshader",
                               "shaders/fragment_shader.fragmentshader");

  // set machine.ctx;

  glClearColor(0.0, 0.05, 0.3, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  GLuint MatrixID = glGetUniformLocation(program, "MVP");

  // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive
  // vertices give a triangle. A cube has 6 faces with 2 triangles each, so this
  // makes 6*2=12 triangles, and 12*3 vertices
  static const GLfloat g_vertex_buffer_data[] = {
      // the cube
      -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
      -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
      -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
      1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f,

      // a triangle
      2, 2, 2, 2, 1, 2, 1, 1, 2};

  // One color for each vertex. They were generated randomly.
  static GLfloat g_color_buffer_data[12 * 3 * 3 + 3];
  for (int v = 0; v < 12 * 3; v++) {
    g_color_buffer_data[3 * v + 0] =
        0.5 + (float)rand() / (float)(RAND_MAX / 0.2);
    g_color_buffer_data[3 * v + 1] =
        0 + (float)rand() / (float)(RAND_MAX / 0.2);
    g_color_buffer_data[3 * v + 2] =
        0.5 + (float)rand() / (float)(RAND_MAX / 0.2);
  }
  g_color_buffer_data[12 * 3 * 3 + 1] = 1;
  g_color_buffer_data[12 * 3 * 3 + 1] = 1;
  g_color_buffer_data[12 * 3 * 3 + 1] = 1;

  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

  GLuint colorbuffer;
  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data),
               g_color_buffer_data, GL_STATIC_DRAW);

  main_loop_data_t data = {machine};

  start_time = SDL_GetTicks();
#ifdef __EMSCRIPTEN__
  void* d = &data;
  emscripten_set_main_loop_arg(main_loop, d, 0, 1);
#else

  while (1) {
    glm::mat4 Projection = glm::perspective(
        glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 View =
        glm::lookAt(glm::vec3(3, 5, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 MVP = Projection * View * Model;
    // do stuff
    main_loop(&data);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(program);

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0,
                 13 * 3);  // 12*3 indices starting at 0 -> 12 triangles

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Swap buffers
    SDL_GL_SwapWindow(window);
    SDL_Delay(1);
  }
#endif

  return 0;
}
