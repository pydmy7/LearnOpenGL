#include "test/shaderprogram.hpp"


#include "util/util.hpp"

#include <cstdint>
#include <iostream>
#include <malloc.h>


ShaderProgram::ShaderProgram(const std::filesystem::path& vertexpath, const std::filesystem::path& fragmentpath) {
    const std::string vertexshadersource {util::readFileToString(vertexpath)};
    const std::string fragmentshadersource {util::readFileToString(fragmentpath)};

    uint32_t vertexshader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexshadersourcecstr = vertexshadersource.c_str();
    glShaderSource(vertexshader, 1, &vertexshadersourcecstr, nullptr);
    glCompileShader(vertexshader);
    checkError(vertexshader, ShaderStage::vertex);

    uint32_t fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentshadersourcecstr = fragmentshadersource.c_str();
    glShaderSource(fragmentshader, 1, &fragmentshadersourcecstr, nullptr);
    glCompileShader(fragmentshader);
    checkError(fragmentshader, ShaderStage::fragment);

    uint32_t shaderprogram = glCreateProgram();
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

void ShaderProgram::use() const {
    glUseProgram(this->shaderprogramid);
}

uint32_t ShaderProgram::getShaderProgramId() const {
    return this->shaderprogramid;
};

void ShaderProgram::setValueFloat(const std::string& name, float_t value) const {
    this->use();
    glUniform1f(glGetUniformLocation(this->shaderprogramid, name.c_str()), value);
}

void ShaderProgram::setValueInt(const std::string& name, int32_t value) const {
    this->use();
    glUniform1i(glGetUniformLocation(this->shaderprogramid, name.c_str()), value);
}

void ShaderProgram::checkError(uint32_t shaderid, ShaderStage stage) const {
    if (stage == ShaderStage::vertex) {
        int32_t success {};
        glGetShaderiv(shaderid, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            int32_t length;
            glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &length);
            GLchar* infolog {static_cast<GLchar*>(alloca(length * sizeof(GLchar)))};
            glGetShaderInfoLog(shaderid, length, nullptr, infolog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
        }
    } else if (stage == ShaderStage::fragment) {
        int32_t success {};
        glGetShaderiv(shaderid, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            int32_t length;
            glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &length);
            GLchar* infolog {static_cast<GLchar*>(alloca(length * sizeof(GLchar)))};
            glGetShaderInfoLog(shaderid, length, nullptr, infolog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
        }
    } else {
        int32_t success {};
        glGetProgramiv(shaderid, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {
            int32_t length;
            glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &length);
            GLchar* infolog {static_cast<GLchar*>(alloca(length * sizeof(GLchar)))};
            glGetProgramInfoLog(shaderid, length, nullptr, infolog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
        }
    }
}
