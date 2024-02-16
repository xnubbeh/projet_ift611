#ifndef TEXTURE_H
#define TEXTURE_H

/*
	Ce fichier est base sur l'engin du TP2 d'IMN401 par Guillaume Gilet. Beaucoup de modifications ont été apportées.
*/

#include <string>
#include <glad/glad.h>

#define TEXTURE_PATH "WowKiller_sheet.png"

class SpriteSheet
{
public:
	SpriteSheet(const std::string& filename);

	~SpriteSheet() = default;

	void loadToGPU();

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
