#ifndef SHADER_PIPELINE_H
#define SHADER_PIPELINE_H

#include <string>

#include <glad/glad.h>
#include <glm.hpp>

#define VERT_SHADER "sprite.vs"
#define FRAG_SHADER "sprite.frag"
#define MAIN_SHADER_NAME "main"

class ShaderPipeline
{
public:
    void Bind();
    void Release();

    // constructor
    ShaderPipeline(std::string name);
    ShaderPipeline() { ShaderPipeline{ "" }; }

    // compiles the shader from given source code
    void Compile(const char* vertexSource, const char* fragmentSource);
    // utility functions
    void SetFloat(const char* name, float value, GLuint shader);
    void SetInteger(const char* name, int value, GLuint shader);
    void SetVector2f(const char* name, float x, float y, GLuint shader);
    void SetVector2f(const char* name, const glm::vec2& value, GLuint shader);
    void SetVector3f(const char* name, float x, float y, float z, GLuint shader);
    void SetVector3f(const char* name, const glm::vec3& value, GLuint shader);
    void SetVector4f(const char* name, float x, float y, float z, float w, GLuint shader);
    void SetVector4f(const char* name, const glm::vec4& value, GLuint shader);
    void SetMatrix4(const char* name, const glm::mat4& matrix, GLuint shader);

    GLuint VertexShader() { return vertexShaderProgram; }
    GLuint FragmentShader() { return fragmentShaderProgram; }

private:

    void checkCompileErrors(unsigned int object, std::string type);
    std::string name;
    // Pipeline
    GLuint shaderProgramPipeline{ 0 };
    // Vertex shader
    GLuint vertexShaderProgram;
    // Fragment shader
    GLuint fragmentShaderProgram;

};

#endif
