/*
	Ce fichier est base sur l'engin du TP2 d'IMN401 par Guillaume Gilet
*/

#include "../header/texture.h"


#include <../third_party/stb_image.h>


Texture::Texture(const std::string& filename) :
	name(filename), id(0), handle(0), format(GL_RGBA8), image(NULL)
{
	int channels;


	image = stbi_load(filename.c_str(), &sprite_sheet_width, &sprite_sheet_height, &channels, 4);

	if (image != nullptr) {
		loadToGPU();
		pixel_height = 1 / sprite_sheet_height;
		pixel_width = 1 / sprite_sheet_width;
	}
		
		//TODO
		// LOG INSTEAD
		// DO SOME ERROR HANDLING

	stbi_image_free(image);
}

void Texture::loadToGPU()
{
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// IMAGE MUST BE MINIMUM 1024x1024
	glTexImage2D(id, 0, GL_SRGB8_ALPHA8, sprite_sheet_width, sprite_sheet_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}
