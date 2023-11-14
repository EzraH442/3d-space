#include <GL/glew.h>
#include <SDL.h>

#include <ctime>
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

void mat4x4_ortho(t_mat4x4 out, float left, float right, float bottom,
                  float top, float znear, float zfar) {
#define T(a, b) (a * 4 + b)

  out[T(0, 0)] = 2.0f / (right - left);
  out[T(0, 1)] = 0.0f;
  out[T(0, 2)] = 0.0f;
  out[T(0, 3)] = 0.0f;

  out[T(1, 1)] = 2.0f / (top - bottom);
  out[T(1, 0)] = 0.0f;
  out[T(1, 2)] = 0.0f;
  out[T(1, 3)] = 0.0f;

  out[T(2, 2)] = -2.0f / (zfar - znear);
  out[T(2, 0)] = 0.0f;
  out[T(2, 1)] = 0.0f;
  out[T(2, 3)] = 0.0f;

  out[T(3, 0)] = -(right + left) / (right - left);
  out[T(3, 1)] = -(top + bottom) / (top - bottom);
  out[T(3, 2)] = -(zfar + znear) / (zfar - znear);
  out[T(3, 3)] = 1.0f;

#undef T
}

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

  glewInit();
  StateMachine machine;

  GLuint program = LoadShaders("shaders/vertex_shader.vertexshader",
                               "shaders/fragment_shader.fragmentshader");

  glDisable(GL_DEPTH_TEST);
  glClearColor(0.5, 0.0, 0.0, 0.0);
  glViewport(0, 0, width, height);

  GLuint vao, vbo;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(attrib_position);
  glEnableVertexAttribArray(attrib_color);

  glVertexAttribPointer(attrib_color, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
                        0);
  glVertexAttribPointer(attrib_position, 2, GL_FLOAT, GL_FALSE,
                        sizeof(float) * 6, (void*)(4 * sizeof(float)));

  const GLfloat g_vertex_buffer_data[] = {
      /*  R, G, B, A, X, Y  */
      1, 0, 0, 1, 0, 0, 0, 1, 0, 1, width, 0,      0, 0, 1, 1, width, height,

      1, 0, 0, 1, 0, 0, 0, 0, 1, 1, width, height, 1, 1, 1, 1, 0,     height};

  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

  t_mat4x4 projection_matrix;
  mat4x4_ortho(projection_matrix, 0.0f, (float)width, (float)height, 0.0f, 0.0f,
               100.0f);
  glUniformMatrix4fv(glGetUniformLocation(program, "u_projection_matrix"), 1,
                     GL_FALSE, projection_matrix);
  main_loop_data_t data = {machine};

  start_time = SDL_GetTicks();
#ifdef __EMSCRIPTEN__
  void* d = &data;
  emscripten_set_main_loop_arg(main_loop, d, 0, 1);
#else

  while (1) {
    // do stuff
    main_loop(&data);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    SDL_GL_SwapWindow(window);
    SDL_Delay(1);
  }
#endif

  return 0;
}
