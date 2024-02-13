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
Texture::Texture(int _width, int _height, GLint _format) :
	sprite_sheet_width(_width), sprite_sheet_height(_height), format(_format)
{

	createEmptyTexture();

}

void Texture::createEmptyTexture()
{
	int numberOfLevel = (int)(1 + floor(log2(std::max(sprite_sheet_width, sprite_sheet_height))));
	glCreateTextures(GL_TEXTURE_2D, 1, &id);

	glTextureStorage2D(id, numberOfLevel, format, sprite_sheet_width, sprite_sheet_height);

	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateTextureMipmap(id);
	makeResident();
}

void Texture::loadToGPU()
{
	createEmptyTexture();

	glTextureSubImage2D(id, 0, 0, 0, sprite_sheet_width, sprite_sheet_height, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateTextureMipmap(id);
}

void Texture::makeResident()
{
	handle = glGetTextureHandleARB(id);
	glMakeTextureHandleResidentARB(handle);

}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}
