#pragma once

#include <glm/glm.hpp>

class Shader
{
public:
        
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Bind();
    void Unbind();

    inline unsigned int GetID() const { return ProgramID; }
  
    void SetInt(const char* name, int value) const;  
    void SetFloat(const char* name, float value) const;
    void SetVec3(const char* name, const glm::vec3& value) const;
    void SetVec4(const char* name, const glm::vec4& value) const;
    void SetMat4(const char* name, const glm::mat4& mat) const;

private:
    void CheckCompileErrors(unsigned int shader, const char* type);
    unsigned int ProgramID;
};