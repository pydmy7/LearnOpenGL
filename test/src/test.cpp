#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "config.h"
#include "test/shaderprogram.hpp"

#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <array>
#include <string>

const std::filesystem::path projectroot {SOURCE_DIR};
const std::filesystem::path shaderdir {projectroot / "shader"};
const std::filesystem::path shadervertfile {shaderdir / "shader.vert"};
const std::filesystem::path orangefragfile {shaderdir / "orange.frag"};
const std::filesystem::path yellowfragfile {shaderdir / "yellow.frag"};

void initGlfw() {
    if (!glfwInit()) {
        glfwTerminate();
        throw std::runtime_error("Failed to initalize GLFW\n");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


int main() {
    initGlfw();

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window\n");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, []([[maybe_unused]] GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD\n");
    }
    std::clog << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';

    std::array<ShaderProgram, 2> shaderprograms {
        ShaderProgram{shadervertfile, orangefragfile},
        ShaderProgram{shadervertfile, yellowfragfile},
    };
    shaderprograms[0].setValueFloat("dx", 0.5);
    shaderprograms[1].setValueFloat("dy", 0.5);

    // ***********************************************************

    std::array<GLfloat, 3 * 3> vertices0 {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };

    std::array<GLfloat, 3 * 3> vertices1 {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };

    std::array<GLuint, 2> VAO, VBO;
    {
        glGenVertexArrays(VAO.size(), VAO.data());
        glGenBuffers(VBO.size(), VBO.data());
        
        // 0
        glBindVertexArray(VAO[0]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        // 0

        // 1
        glBindVertexArray(VAO[1]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        // 1
    }

    auto render = [&]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderprograms[0].use();
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, vertices0.size() / 3);
        
        shaderprograms[1].use();
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() / 3);
    };

    // ***********************************************************

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO.data());
    glDeleteBuffers(2, VBO.data());

    glfwTerminate();

    return 0;
}
