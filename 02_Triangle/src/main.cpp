
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
  glViewport(0, 0, 640, 480); // Is this call necessary?
  // Registers the callback function.
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


  //Set Up and Compile the Shaders
  uint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  

  //Set up vertices of the triangle
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
  };

  uint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.5f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Handle input

    // Handle rendering

    glfwSwapBuffers(window);

    glfwPollEvents();
  }
  cout << "Window successfully closed." << endl;

  glfwTerminate();
  return 0;
}
