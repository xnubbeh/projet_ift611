#include "../header/shader_pipeline.h"

#include <iostream>
#include "gtc/type_ptr.hpp"
#include "../header/utils.h"

ShaderPipeline::ShaderPipeline(std::string name) : name {name} {}


void ShaderPipeline::Compile(const char* vertexSource, const char* fragmentSource)
{
    std::string vertexCodeStr = readFile(vertexSource);
    std::string fragmentCodeStr = readFile(fragmentSource);
    const GLchar* vertexCode = vertexCodeStr.c_str();
    const GLchar* fragmentCode = fragmentCodeStr.c_str();

    glCreateProgramPipelines(1, &shaderProgramPipeline);

    // vertex Shader
    vertexShaderProgram = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vertexCode);
    checkCompileErrors(vertexShaderProgram, "VERTEX");
    // fragment Shader
    fragmentShaderProgram = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragmentCode);
    checkCompileErrors(fragmentShaderProgram, "FRAGMENT");

    // shader program
    glUseProgramStages(shaderProgramPipeline, GL_VERTEX_SHADER_BIT, vertexShaderProgram);
    glUseProgramStages(shaderProgramPipeline, GL_FRAGMENT_SHADER_BIT, fragmentShaderProgram);

    glValidateProgramPipeline(shaderProgramPipeline);
    glBindProgramPipeline(shaderProgramPipeline);
    checkCompileErrors(shaderProgramPipeline, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShaderProgram);
    glDeleteShader(fragmentShaderProgram);
}

void ShaderPipeline::SetFloat(const char* name, float value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform1f(shader, variable,  value);
}
void ShaderPipeline::SetInteger(const char* name, int value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform1i(shader, variable, value);
}
void ShaderPipeline::SetVector2f(const char* name, float x, float y, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform2f(shader, variable, x, y);
}
void ShaderPipeline::SetVector2f(const char* name, const glm::vec2& value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform2f(shader, variable, value.x, value.y);
}
void ShaderPipeline::SetVector3f(const char* name, float x, float y, float z, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform3f(shader, variable, x, y, z);
}
void ShaderPipeline::SetVector3f(const char* name, const glm::vec3& value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform3f(shader, variable, value.x, value.y, value.z);
}
void ShaderPipeline::SetVector4f(const char* name, float x, float y, float z, float w, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform4f(shader, variable, x, y, z, w);
}
void ShaderPipeline::SetVector4f(const char* name, const glm::vec4& value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform4f(shader, variable, value.x, value.y, value.z, value.w);
}
void ShaderPipeline::SetMatrix4(const char* name, const glm::mat4& matrix, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniformMatrix4fv(shader, variable, 1, false, glm::value_ptr(matrix));
}

void ShaderPipeline::checkCompileErrors(unsigned int object, std::string type)
{// TODO : LOG INSTEAD OF COUT
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}

void ShaderPipeline::Bind() {
    glBindProgramPipeline(shaderProgramPipeline);
}

void ShaderPipeline::Release() {
    glBindProgramPipeline(0);
}
