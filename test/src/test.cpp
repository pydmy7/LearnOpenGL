#include "config.h"

#include "test/shaderprogram.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <array>
#include <string>


namespace fs = std::filesystem;


const fs::path projectroot {SOURCE_DIR};
const fs::path shaderdir {projectroot / "shader"};
const fs::path texturevs {shaderdir / "texture.vs"};
const fs::path texturefs {shaderdir / "texture.fs"};


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

    // ***********************************************************

    std::array<ShaderProgram, 1> shaderprograms {
        ShaderProgram{texturevs, texturefs}
    };

    std::array<GLuint, 1> VAO, VBO, EBO;
    {
        glGenVertexArrays(VAO.size(), VAO.data());
        glGenBuffers(VBO.size(), VBO.data());
        glGenBuffers(EBO.size(), EBO.data());

        std::array<GLfloat, 20> vertices {
            // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
        };

        std::array<GLuint, 6> indices {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        
        // 0
        {
            glBindVertexArray(VAO[0]);

            glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                5 * sizeof(float), reinterpret_cast<void*>(0));
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        // 0
    }

    std::array<GLuint, 2> textures;
    {
        glGenTextures(textures.size(), textures.data());

        // 0
        {
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int width, height, nrChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load("resources/textures/container.jpg",
                &width, &height, &nrChannels, 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                    width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cerr << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
        }
        // 0

        // 1
        {
            glBindTexture(GL_TEXTURE_2D, textures[1]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int width, height, nrChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load("resources/textures/awesomeface.png",
                &width, &height, &nrChannels, 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                    width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
        }
        // 1
    }

    shaderprograms[0].setValueInt("texture0", 0);
    shaderprograms[0].setValueInt("texture1", 1);

    auto render = [&]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);

        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

        shaderprograms[0].use();
        unsigned int transformLoc = glGetUniformLocation(shaderprograms[0].getShaderProgramId(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    };

    // ***********************************************************

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(VAO.size(), VAO.data());
    glDeleteBuffers(VBO.size(), VBO.data());
    glDeleteBuffers(EBO.size(), EBO.data());

    glfwTerminate();

    return 0;
}
