#pragma once

#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <vector>

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/#shader-compilation
GLuint LoadShaders(const char* vertex_file_path,
                   const char* fragment_file_path) {
  // Create the shaders
  GLuint vs, fs;
  vs = glCreateShader(GL_VERTEX_SHADER);
  fs = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vertexShaderCode;
  std::string fragmentShaderCode;

  std::ifstream vss(vertex_file_path, std::ios::in);
  std::ifstream fss(fragment_file_path, std::ios::in);

  int fail = !vss.is_open() || !fss.is_open();

  if (fail) {
    return 0;
  }

  // Read the Vertex Shader code from the file
  std::stringstream vsstr;
  vsstr << vss.rdbuf();
  vertexShaderCode = vsstr.str();
  vss.close();

  // Read the Fragment Shader code from the file
  std::stringstream fsstr;
  fsstr << fss.rdbuf();
  fragmentShaderCode = fsstr.str();
  fss.close();

  GLint status = GL_FALSE;
  int InfoLogLength;

  // compile shaders
  printf("Compiling shader : %s\n", vertex_file_path);
  char const* vp = vertexShaderCode.c_str();
  glShaderSource(vs, 1, &vp, NULL);
  glCompileShader(vs);

  printf("Compiling shader : %s\n", fragment_file_path);
  char const* fp = fragmentShaderCode.c_str();
  glShaderSource(fs, 1, &fp, NULL);
  glCompileShader(fs);

  // check shaders
  glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
  glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(vs, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
  glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(fs, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }

  // Link the program
  printf("Linking program\n");
  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  // Check the program
  // glGetProgramiv(program, GL_LINK_STATUS, &status);
  // glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
  // if (InfoLogLength > 0) {
  //   std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
  //   glGetProgramInfoLog(program, InfoLogLength, NULL,
  //   &ProgramErrorMessage[0]); printf("%s\n", &ProgramErrorMessage[0]);
  // }

  glUseProgram(program);
  return program;
}