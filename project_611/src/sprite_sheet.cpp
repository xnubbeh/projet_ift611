/*
	Ce fichier est base sur l'engin du TP2 d'IMN401 par Guillaume Gilet. Plusieurs modifications ont été apportées
*/

#define STB_IMAGE_IMPLEMENTATION
#include <../third_party/stb_image.h>

#include "../header/sprite_sheet.h"

SpriteSheet::SpriteSheet(const std::string& filename) :
	name(filename), id(0), handle(0), format(GL_RGBA8), image(NULL)
{
	int channels;

	image = stbi_load(filename.c_str(), &sprite_sheet_width, &sprite_sheet_height, &channels, 4);
	
	if (image == nullptr) {
		// TODO
		// LOG INSTEAD
		// DO SOME ERROR HANDLING
	}

	loadToGPU();
	pixel_height = 1 / sprite_sheet_height;
	pixel_width = 1 / sprite_sheet_width;

	stbi_image_free(image);
}

void SpriteSheet::loadToGPU()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, sprite_sheet_width, sprite_sheet_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_FRAMEBUFFER_SRGB);
}

void SpriteSheet::Bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}
