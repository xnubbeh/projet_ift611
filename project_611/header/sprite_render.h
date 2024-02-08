#ifndef SPRITE_REDNER_H
#define SPRITE_RENDER_H



#include <glad/glad.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "texture.h"
#include "shader_pipeline.h"

class sprite_render
{
public:
	sprite_render(ShaderPipeline& shader);
	~sprite_render();
	void DrawSprite(Texture& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
	ShaderPipeline shader;
	GLuint quadVAO;
	void initRenderData();
};

#endif // !1