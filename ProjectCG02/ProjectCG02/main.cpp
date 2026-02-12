#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

using namespace std;

// ÕÃ„ «·‰«›–…

const GLint SCR_WIDTH = 800;
const GLint SCR_HEIGHT = 600;

// ﬂÊœ «·‹ Vertex Shader

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"}\0";

// ﬂÊœ «·‹ Fragment Shader

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec3 color;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(color, 1.0);\n"
"}\n\0";

// œ«·… · €ÌÌ— ÕÃ„ ‰«›–… «·⁄—÷

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// œ«·… ·„⁄«·Ã… «·≈œŒ«· „‰ «·ﬂÌ»Ê—œ

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //  ÂÌ∆… GLFW

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ≈‰‘«¡ ‰«›–…

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rotating Rectangle", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //  ÂÌ∆… GLEW

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        return -1;

    // ≈‰‘«¡ Ê Ã„Ì⁄ «·‹ Vertex Shader

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // ≈‰‘«¡ Ê Ã„Ì⁄ «·‹ Fragment Shader

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

     
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //  (≈Õœ«ÀÌ«  «·„” ÿÌ·  („ﬂÊ‰ „‰ „À·ÀÌ‰

    float vertices[] = {
        -0.6f, -0.35f, 0.0f,
         0.6f, -0.35f, 0.0f,
         0.6f,  0.35f, 0.0f,

        -0.6f, -0.35f, 0.0f,
         0.6f,  0.35f, 0.0f,
        -0.6f,  0.35f, 0.0f
    };

    // ≈‰‘«¡ VAO Ê VBO

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // —»ÿ VAO Ê VBO

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //VBO  ÕœÌœ ﬂÌ›Ì… ﬁ—«¡… «·»Ì«‰«  „‰ 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Õ·ﬁ… «·—”„ «·—∆Ì”Ì…
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //·Ê‰ «·Œ·›Ì… .. ﬂÕ·Ì Â«œ∆


        glClearColor(0.15f, 0.18f, 0.30f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       

        glUseProgram(shaderProgram);

        // Õ”«» “Ê«Ì« «·œÊ—«‰ Õ”» «·“„‰

        float time = glfwGetTime();
        float angleX = time;
        float angleY = time * 0.7f;
        float angleZ = time * 0.4f;

        //    „’›Ê›…«·œÊ—«‰  ..  (XÊYÊZ)  «·œÊ—«‰ ⁄·Ï «·„Õ«Ê— «·À·«À
         
        float transform[16] = {
            cos(angleY) * cos(angleZ), -cos(angleY) * sin(angleZ), sin(angleY), 0.0f,
            cos(angleX) * sin(angleZ) + sin(angleX) * sin(angleY) * cos(angleZ), cos(angleX) * cos(angleZ) - sin(angleX) * sin(angleY) * sin(angleZ), -sin(angleX) * cos(angleY), 0.0f,
            sin(angleX) * sin(angleZ) - cos(angleX) * sin(angleY) * cos(angleZ), sin(angleX) * cos(angleZ) + cos(angleX) * sin(angleY) * sin(angleZ), cos(angleX) * cos(angleY), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        // ≈—”«· „’›Ê›… «· ÕÊÌ· ≈·Ï «·‘Ìœ—

        int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform);

        // (≈—”«· ·Ê‰ «·„” ÿÌ· (“Â—Ì

        int colorLoc = glGetUniformLocation(shaderProgram, "color");
        glUniform3f(colorLoc, 1.0f, 0.3f, 0.6f);

        // —”„ «·„” ÿÌ·

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

      
        //  ÕœÌÀ «·≈ÿ«— Ê„⁄«·Ã… «·√Õœ«À

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //  ‰ŸÌ› «·–«ﬂ—…

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}