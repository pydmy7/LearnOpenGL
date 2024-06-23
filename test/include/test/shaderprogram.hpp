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
    GLuint shaderprogramid;

    ShaderProgram(const std::filesystem::path& vertexpath, const std::filesystem::path& fragmentpath);
    ~ShaderProgram();

    void use();

    void setValueFloat(const std::string& name, float value);

private:
    void checkError(GLuint shaderid, ShaderStage stage);
};
