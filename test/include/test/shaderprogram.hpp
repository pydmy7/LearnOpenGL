#pragma once


#include <glad/glad.h>

#include <filesystem>


enum class ShaderStage {
    vertex,
    fragment,
    program
};


class ShaderProgram final {
public:
    ShaderProgram(const std::filesystem::path& vertexpath, const std::filesystem::path& fragmentpath);
    ~ShaderProgram();

    void use();
    GLuint getShaderProgramId() const;
    void setValueFloat(const std::string& name, GLfloat value);
    void setValueInt(const std::string& name, GLint value);

private:
    GLuint shaderprogramid;
    void checkError(GLuint shaderid, ShaderStage stage);
};
