#ifndef TEXTURE_H
#define TEXTURE_H

/*
	Ce fichier est base sur l'engin du TP2 d'IMN401 par Guillaume Gilet
*/

// TODO
// Refactor name to sprite sheet

#include <string>
#include <glad/glad.h>

class Texture
{
public:
	Texture(const std::string& filename);

	//Create an empty texture
	Texture(int _width = 1024, int _height = 1024);

	//Create an empty texture
	Texture(int _width = 1024, int _height = 1024, GLint format = GL_RGBA8);

	~Texture() = default;

	void createEmptyTexture();
	void loadToGPU();
	void makeResident();

	void Bind();

	GLuint getId() {
		return id;
	};
	GLuint64 getHandle()
	{
		return handle;
	};

	int sprite_sheet_width, sprite_sheet_height; //might have to make getter & setter
	float pixel_width, pixel_height; //might have to make getter & setter

protected:
	GLuint id;
	GLuint64 handle;
	std::string name;
	
	GLint format;
	unsigned char* image;
};

#endif // TEXTURE_H
