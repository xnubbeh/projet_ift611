#ifndef SPRITE_H
#define SPRITE_H



#include <glad/glad.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "texture.h"
#include "shader_pipeline.h"
#include "frame.h"
#include "singleton.h"

#define MAX_SPRITES 1000

struct RenderData {
	glm::vec2 pos;  // Top left of the sprite
	glm::vec2 size; // vec2(width, height);
	glm::ivec2 atlasOffset;
	glm::ivec2 spriteSize; // vec2(numPix_width, numPix_height);
	float z;
};

class Sprite : public Singleton<Sprite> {
	friend class Singleton<Sprite>;
public:
	// vieille sauce
	Sprite();
	~Sprite();
	void Render(Frame* frame_pointer);

	// sauce fraiche
	void RenderAll();
	int AddSprite(const RenderData& data); // retourne l'indice de ce sprite dans renderData[]
	void Init();
	
private:
	void InitBuffers();

	// Buffers
	GLuint VAO /*VertexArray*/,
		   VBO /*Base vertex*/,
		   VBO_POSITION /*Vertex position and size*/,
		   VBO_SPRITE /*Atlas offset and sprite size*/,
		   VBO_DEPTH /*z-buffer*/;

	ShaderPipeline main_shader;

	// RenderData arrays
//	RenderData renderData[MAX_SPRITES];
	glm::vec4 positionOffset_size [MAX_SPRITES];
	glm::ivec4 atlasOffset_spriteSize [MAX_SPRITES];
	float zBuffer[MAX_SPRITES];

	int numSprites;
	Texture sprite_sheet;

};

#endif // !1