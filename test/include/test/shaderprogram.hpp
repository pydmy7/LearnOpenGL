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

    void use() const;
    uint32_t getShaderProgramId() const;
    void setValueFloat(const std::string& name, GLfloat value) const;
    void setValueInt(const std::string& name, GLint value) const;

private:
    uint32_t shaderprogramid;
    
    void checkError(uint32_t shaderid, ShaderStage stage) const;
};
