
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

#define uint unsigned int


// NOTE: My portable laptop only supports opengl v3.0 (glsl 130)
// It does not support explicit attribute locations in vertex shaders.
// As such, the following will not work:
// "layout (location = 0) in vec3 aPos;\n"
// I had to use glBindAttribLocation() instead

const char *vertexShaderSource = "#version 130\n"
  "attribute vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragmentShaderSource = "#version 130\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

/*
 * Callback function that allows the opengl render window to update
 * when the window is resized.
 * NOTE: This is automatically called by glfw
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}


int main(int argc, char *argv[]) {
  GLFWwindow* window;

  cout << "Starting." << endl;
  // Initialize
  if (!glfwInit()) {
    return -1;
  }

  window = glfwCreateWindow(640, 480, "Test" , NULL, NULL);

  if (!window) {
    cout << "Failed to create window." << endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  cout << "Window successfully created." << endl;

  // Set the size of the opengl render window
  //glViewport(0, 0, 640, 480); // Is this call necessary?
  // Registers the callback function.
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  GLenum err = glewInit();

  if (GLEW_OK != err) {
    cout << "GLEW failed to initialize" << endl;
    return -1;
  }

  // Set Up and Compile the Shaders
  int success;
  char infoLog[512];

  // Vertex Shader
  uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
    cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
  }

  // Fragment Shader
  uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
  glCompileShader(fragmentShader);
  
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
    cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
  }

  uint shaderProgram = glCreateProgram();
  glBindAttribLocation(shaderProgram, 0, "aPos");
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
    cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Set up vertices of the triangle
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
  };

  uint VBO, VAO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Handle input

    // Handle rendering
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }
  cout << "Window successfully closed." << endl;

  glfwTerminate();
  return 0;
}
