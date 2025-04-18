#include <cstdio>
#include <cstring>

#include <glad/glad.h>    
#include <GLFW/glfw3.h>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

// GL objects
GLuint VBO, VAO, shader;

// Vertex Shader source
static const char *vShader = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 pos;
    void main() {
        gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
    }
)glsl";

// Fragment Shader source
static const char *fShader = R"glsl(
    #version 330 core
    out vec4 colour;
    void main() {
        colour = vec4(1.0, 0.5, 0.0, 1.0);
    }
)glsl";

void CreateTriangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f};

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    printf("Created Triangle\n");
}

void AddShader(GLuint prog, const char *src, GLenum type)
{
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        char log[512];
        glGetShaderInfoLog(s, sizeof(log), nullptr, log);
        fprintf(stderr, "Shader compile error: %s\n", log);
        return;
    }
    glAttachShader(prog, s);
}

void CompileShaders()
{
    shader = glCreateProgram();
    if (!shader)
    {
        fprintf(stderr, "Failed to create shader program\n");
        return;
    }
    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    glLinkProgram(shader);
    GLint ok;
    glGetProgramiv(shader, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        char log[512];
        glGetProgramInfoLog(shader, sizeof(log), nullptr, log);
        fprintf(stderr, "Program link error: %s\n", log);
        return;
    }
    glValidateProgram(shader);
}

void ProcessInput(GLFWwindow *win)
{
    if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, true);
}

int main()
{
    printf("Starting...\n");

    if (!glfwInit())
    {
        fprintf(stderr, "GLFW initialization failed\n");
        return -1;
    }

    // Request OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Limitless", nullptr, nullptr);
    if (!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD before calling any OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    // Set viewport
    int bw, bh;
    glfwGetFramebufferSize(window, &bw, &bh);
    glViewport(0, 0, bw, bh);

    CreateTriangle();
    CompileShaders();

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        glfwPollEvents();

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
