#include "test/shaderprogram.hpp"


#include "util/util.hpp"

#include <iostream>
#include <malloc.h>


ShaderProgram::ShaderProgram(const std::filesystem::path& vertexpath, const std::filesystem::path& fragmentpath) {
    const std::string vertexshadersource {util::readFileToString(vertexpath)};
    const std::string fragmentshadersource {util::readFileToString(fragmentpath)};

    GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexshadersourcecstr = vertexshadersource.c_str();
    glShaderSource(vertexshader, 1, &vertexshadersourcecstr, nullptr);
    glCompileShader(vertexshader);
    checkError(vertexshader, ShaderStage::vertex);

    GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentshadersourcecstr = fragmentshadersource.c_str();
    glShaderSource(fragmentshader, 1, &fragmentshadersourcecstr, nullptr);
    glCompileShader(fragmentshader);
    checkError(fragmentshader, ShaderStage::fragment);

    GLuint shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram, vertexshader);
    glAttachShader(shaderprogram, fragmentshader);
    glLinkProgram(shaderprogram);
    checkError(shaderprogram, ShaderStage::program);

    glValidateProgram(shaderprogram);
    
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);

    this->shaderprogramid = shaderprogram;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->shaderprogramid);
}

void ShaderProgram::use() {
    glUseProgram(this->shaderprogramid);
}

GLuint ShaderProgram::getShaderProgramId() const {
    return this->shaderprogramid;
};

void ShaderProgram::setValueFloat(const std::string& name, GLfloat value) {
    this->use();
    glUniform1f(glGetUniformLocation(this->shaderprogramid, name.c_str()), value);
}

void ShaderProgram::setValueInt(const std::string& name, GLint value) {
    this->use();
    glUniform1i(glGetUniformLocation(this->shaderprogramid, name.c_str()), value);
}

void ShaderProgram::checkError(GLuint shaderid, ShaderStage stage) {
    if (stage == ShaderStage::vertex) {
        GLint success {};
        glGetShaderiv(shaderid, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            GLint length;
            glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &length);
            GLchar* infolog {static_cast<GLchar*>(alloca(length * sizeof(GLchar)))};
            glGetShaderInfoLog(shaderid, length, nullptr, infolog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
        }
    } else if (stage == ShaderStage::fragment) {
        GLint success {};
        glGetShaderiv(shaderid, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            GLint length;
            glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &length);
            GLchar* infolog {static_cast<GLchar*>(alloca(length * sizeof(GLchar)))};
            glGetShaderInfoLog(shaderid, length, nullptr, infolog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
        }
    } else {
        GLint success {};
        glGetProgramiv(shaderid, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {
            GLint length;
            glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &length);
            GLchar* infolog {static_cast<GLchar*>(alloca(length * sizeof(GLchar)))};
            glGetProgramInfoLog(shaderid, length, nullptr, infolog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
        }
    }
}
