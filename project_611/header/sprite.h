#ifndef SPRITE_H
#define SPRITE_H



#include <glad/glad.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "texture.h"
#include "shader_pipeline.h"
#include "frame.h"

class Sprite
{
public:
	Sprite(const ShaderPipeline& shader, const Texture& sprite_sheet, const glm::vec2& sprite_sheet_position);
	~Sprite();
	void Render(Frame* frame_pointer);
	
private:
	ShaderPipeline shader;
	GLuint quadVAO;
	void initRenderData();

	glm::vec2 sprite_sheet_pos;
	Texture sprite_sheet;

};

#endif // !1