#include "../header/sprite.h"

Sprite::Sprite(const ShaderPipeline& shader, const Texture& sprite_sheet, const glm::vec2& sprite_sheet_position) :
    shader{shader},
    sprite_sheet{sprite_sheet},
    sprite_sheet_pos{sprite_sheet_position} 
{

	initRenderData(); // a reviser
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void Sprite::Render(Frame* frame_pointer) {
    shader.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    shader.Release();
}

void Sprite::initRenderData() {
    shader.SetVector2f("caca",sprite_sheet_pos,shader.fragmentShaderProgram); //frag ou vertex
    // 100% integre 

    // configure VAO/VBO
    //GLuint VBO;
    //float vertices[] = {
    //    // pos      // tex
    //    0.0f, 1.0f, 0.0f, 1.0f,
    //    1.0f, 0.0f, 1.0f, 0.0f,
    //    0.0f, 0.0f, 0.0f, 0.0f,

    //    0.0f, 1.0f, 0.0f, 1.0f,
    //    1.0f, 1.0f, 1.0f, 1.0f,
    //    1.0f, 0.0f, 1.0f, 0.0f
    //};

    //glCreateBuffers(1, &VBO);
    //glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glCreateVertexArrays(1, &this->quadVAO);
    //glEnableVertexArrayAttrib(this->quadVAO, 0);
    //glVertexArrayAttribFormat(this->quadVAO, 0, 4, GL_FLOAT, GL_FALSE, 0);
    //glVertexArrayVertexBuffer(this->quadVAO, 0, VBO, 0, sizeof(float) * 4);

    //glVertexArrayAttribBinding(this->quadVAO, 0, 0);
    //glBindVertexArray(this->quadVAO);
}

