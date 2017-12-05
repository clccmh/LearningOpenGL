
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./shader.h"

using namespace std;

#define uint unsigned int


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


  uint vertexShader = read_and_compile_shader("./shaders/vertex.glsl", GL_VERTEX_SHADER);

  uint fragmentShader = read_and_compile_shader("./shaders/fragment.glsl", GL_FRAGMENT_SHADER);

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
