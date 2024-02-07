#include "../header/shader.h"

#include <iostream>
#include "gtc/type_ptr.hpp"

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    GLuint gShader;
    // vertex Shader
    this->vs = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vertexSource);
    checkCompileErrors(this->vs, "VERTEX");
    // fragment Shader
    this->fs = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragmentSource);
    checkCompileErrors(this->fs, "FRAGMENT");

    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShaderProgramv(GL_GEOMETRY_SHADER, 1, &geometrySource);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // shader program
    glCreateProgramPipelines(1, &this->ID);
    glUseProgramStages(this->ID, GL_VERTEX_SHADER_BIT, this->vs);
    glUseProgramStages(this->ID, GL_FRAGMENT_SHADER_BIT, this->fs);

    if (geometrySource != nullptr)
        glUseProgramStages(this->ID, GL_GEOMETRY_SHADER_BIT, gShader);
    glValidateProgramPipeline(this->ID);
    glBindProgramPipeline(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(this->vs);
    glDeleteShader(this->fs);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Shader::SetFloat(const char* name, float value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform1f(shader, variable,  value);
}
void Shader::SetInteger(const char* name, int value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform1i(shader, variable, value);
}
void Shader::SetVector2f(const char* name, float x, float y, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform2f(shader, variable, x, y);
}
void Shader::SetVector2f(const char* name, const glm::vec2& value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform2f(shader, variable, value.x, value.y);
}
void Shader::SetVector3f(const char* name, float x, float y, float z, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform3f(shader, variable, x, y, z);
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform3f(shader, variable, value.x, value.y, value.z);
}
void Shader::SetVector4f(const char* name, float x, float y, float z, float w, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform4f(shader, variable, x, y, z, w);
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniform4f(shader, variable, value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, GLuint shader)
{
    GLint variable = glGetUniformLocation(shader, name);
    glProgramUniformMatrix4fv(shader, variable, 1, false, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(unsigned int object, std::string type)
{
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
