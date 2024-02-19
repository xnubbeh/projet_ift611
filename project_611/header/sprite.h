#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "sprite_sheet.h"
#include "shader_pipeline.h"
#include "singleton.h"

#define MAX_SPRITES 1000

struct RenderData {
	glm::vec2 pos;  // bottom left position of the sprite
	glm::vec2 size; // (width, height)
	glm::vec2 atlasOffset; // top left position of the sprite in the atlas, expressed in texels
	glm::vec2 spriteSize; // (spriteWidth, spriteHeight), expressed in texels
	float z;
};

class Sprite : public Singleton<Sprite> {
	friend class Singleton<Sprite>;
public:

	Sprite();
	~Sprite();

	void RenderAll();
	int AddSprite(const RenderData& data); // retourne l'indice de ce sprite dans renderData[]
	void Init();
	
private:
	void InitBuffers();

	// Buffers
	GLuint VAO /*VertexArray*/,
		   VBO_POSITION /*Vertex position and size*/,
		   VBO_SPRITE /*Atlas offset and sprite size*/,
		   VBO_DEPTH /*z-buffer*/;

	ShaderPipeline main_shader;

	// # # # # RENDER DATA SECTION # # # #
	// Position and size of the object to draw
	//   positionOffset_size.xy = position, positionOffset_size.zw = size
	glm::vec4 positionOffset_size[MAX_SPRITES];

	// Atlas offset and the size of the sprite to draw
	//   atlasOffset_spriteSize.xy = atlas offset, atlasOffset_spriteSize.zw = sprite size
	glm::vec4 atlasOffset_spriteSize [MAX_SPRITES];

	// zBuffer
	float zBuffer[MAX_SPRITES];							

	int numSprites;

	// Currently we only have one sprite_sheet but this could become an array
	SpriteSheet sprite_sheet;

};

#endif // !1