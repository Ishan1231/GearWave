#include <glad/glad.h>    
#include <GLFW/glfw3.h>

#include <iostream>

const GLint WIDTH = 800, HEIGHT = 600;

// Adjusts viewport on incase of resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) // Closes window on escape key press
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{

    // Initializing GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Major version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Minor version 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set profile to core to ignore old deprecated functionality
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac specific set forward compatibility to true
    #endif

    // Create OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Project GearWave", NULL, NULL);
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

    glViewport(0, 0, WIDTH, HEIGHT); // Sets the bottom left corner of the window.
    // Example of a call back function. We can pass in our own custom functions and register them into these functions to perform specific actions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Main game loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State setting function
        glClear(GL_COLOR_BUFFER_BIT); // State using function

        // Check/Call events and swap buffers
        glfwSwapBuffers(window); // OpenGL uses a buffer system to more efficienty draw and swaps between them and draws on the one not displayed 
        glfwPollEvents(); 
    }

    glfwTerminate();
    return 0;
}
