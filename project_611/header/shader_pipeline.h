#ifndef SHADER_PIPELINE_H
#define SHADER_PIPELINE_H

#include <string>

#include <glad/glad.h>
#include <glm.hpp>

//Stuff that will be used a lot so we need it here for ease of use
class ShaderPipeline
{
public:

//public:
//
//    GLProgramPipeline(string name = "");
//
//    ~GLProgramPipeline();
//
//    void useProgramStage(GLProgram* p, GLenum programType);
//    bool link();
//
    void Bind();
    void Release();
//
//    void printInfoLog();
//    GLuint getId();
//
//private:
//    GLuint m_Pipeline;
//    std::string m_Name;
//    string info_text;

    // Pipeline
    GLuint shaderProgramPipeline;
    // Vertex shader
    GLuint vertexShaderProgram;
    // Fragment shader
    GLuint fragmentShaderProgram;
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
private:
    // checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(unsigned int object, std::string type);
    std::string name;

};

#endif
