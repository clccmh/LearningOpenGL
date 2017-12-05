#include "./shader.h"

using namespace std;

unsigned int read_and_compile_shader(char* path, GLenum type) {
  int success;
  char infoLog[512];

  ifstream file(path);
  if (!file.is_open()) {
    cout << "File failed to open: " << path << endl;
  }

  string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

  const char* code = contents.c_str();

  uint shader = glCreateShader(type);
  glShaderSource(shader, 1, &code, 0);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, 0, infoLog);
    cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
  }

  file.close();
  return shader;
}
