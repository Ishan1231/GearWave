#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

const GLint WIDTH = 800, HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
const char *LoadShaderSource(const char *filePath);

int main()
{
  const char *vertexShaderSource = LoadShaderSource("assets/shaders/vertexShader.glsl");     // Vertex Shader source code
  const char *fragmentShaderSource = LoadShaderSource("assets/shaders/fragmentShader.glsl"); // Fragement Shader source code

  // initializing GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // Major version 3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // Minor version 3
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set profile to core to ignore old deprecated functionality

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac specific set forward compatibility to true
#endif

  // Create OpenGL context
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Project GearWave", NULL, NULL);
  if (!window) // Check if window initialized
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window); // Set window pointer to the current context on the current thread

  // Check if glad loader loaded
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Example of a call back function. We can pass in our own custom functions and register them into these functions to perform specific actions
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Shader Code

  // Vertex Shader code
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create shader object and assign the type of shader

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // Checks if shader was compiled

  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  else
  {
    std::cout << "SEEYUH" << std::endl;
  }

  // Fragment Shader code
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // Checks if shader was compiled

  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  else
  {
    std::cout << "SEEYUH" << std::endl;
  }

  // Creating a shader program object to link all shaders
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  else
  {
    std::cout << "SEEYUH" << std::endl;
  }

  glUseProgram(shaderProgram);

  // Delete shaders after linking them since
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Handling Vertices

  // Vertices of a rectangle
  float tri1[] = {
      -0.5f, -0.25f, 0.0f,
      -0.25f, 0.0f, 0.0f,
      0.0f, -0.25f, 0.0f};

  float tri2[] = {
      0.0f, -0.25f, 0.0f,
      0.25f, 0.0f, 0.0f,
      0.5f, -0.25f, 0.0f};

  // VAOs store the vertex data in VBOs for later use
  unsigned int VAO, VBO1, VBO2;
  glGenVertexArrays(1, &VAO);

  // VBOs are objects which can store large amounts of vertex data in the GPU
  glGenBuffers(1, &VBO1); // Generate buffers. Can do as many as you want as long as they have different types
  glGenBuffers(1, &VBO2); // Generate buffers. Can do as many as you want as long as they have different types

  glBindVertexArray(VAO); // Bind vertex array object

  glBindBuffer(GL_ARRAY_BUFFER, VBO1); // Bind the vertex buffer object to the GL_ARRAY_BUFFER buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tri1), tri1, GL_STATIC_DRAW); // Storing user defined vertex data into the curruntly bound buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(tri2), tri2, GL_STATIC_DRAW); // Storing user defined vertex data into the curruntly bound buffer

  // position of the vertex, size of the vertex, type of data, if we want it to be normalized
  // increments at which each vertex attributes are present, weird casting but is the offset of the buffer beginning(idk)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Main game loop
  while (!glfwWindowShouldClose(window))
  {
    // Input
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State setting function
    glClear(GL_COLOR_BUFFER_BIT);         // State using function

    // Rendering
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Check/Call events and swap buffers
    glfwSwapBuffers(window); // OpenGL uses a buffer system to more efficienty draw and swaps between them and draws on the one not displayed
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

// Uses File IO to read and copy a file into a string(const char*)
const char *LoadShaderSource(const char *filePath)
{
  FILE *file = fopen(filePath, "rb");
  if (!file)
  {
    fprintf(stderr, "Failed to open shader file: %s\n", filePath);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = (char *)malloc(length + 1);
  if (!buffer)
  {
    fprintf(stderr, "Failed to allocate memory for shader file.\n");
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, length, file);
  buffer[length] = '\0';
  fclose(file);
  return buffer;
}

// Adjusts viewport on incase of resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

// Checks for input
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Closes window on escape key press
    glfwSetWindowShouldClose(window, GL_TRUE);
}
