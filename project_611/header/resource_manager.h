#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


#include "../third_party/stb_image.h"

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"

class resource_manager
{
public:
    // resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture> Textures;
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // retrieves a stored sader
    static Shader GetShader(std::string name);
    // loads (and generates) a texture from file
    static Texture LoadTexture(const char* file, bool alpha, std::string name);
    // retrieves a stored texture
    static Texture GetTexture(std::string name);
    // properly de-allocates all loaded resources
    static void Clear();

    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    resource_manager() { }
    // loads and generates a shader from file
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    // loads a single texture from file
    static Texture loadTextureFromFile(const char* file, bool alpha);
};

#endif