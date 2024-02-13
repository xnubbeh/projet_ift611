#include "../header/sprite.h"
#include "../header/camera.h"

Sprite::Sprite() :
    shader{ MAIN_SHADER_NAME },
    sprite_sheet{TEXTURE_PATH}
{
	initRenderData(); // a reviser
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void Sprite::Render(Frame* frame_pointer) {
    //shader.Bind();
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //shader.Release();
}

void Sprite::initRenderData() {
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

void Sprite::RenderAll()
{
    // on a un array de *sprites* qu'on veut render
    // le buffer qu'on passe contient un array de structs
        // chaque struct contient le data pour render une sprite individuelle
    
    // if (it has changed) ??
    main_shader.SetMatrix4("orthoProjection", Camera::getInstance()->Projection(), main_shader.vertexShaderProgram);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(RenderData) * numSprites, renderData);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, numSprites + 1);
}


int Sprite::AddSprite(const RenderData& data) {
    renderData[numSprites] = data;
    ++numSprites;
    return numSprites - 1;
}

void Sprite::Init() {
    // Init buffers
    glGenBuffers(1, &SBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(RenderData) * MAX_SPRITES, renderData, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(RenderData) * numSprites, renderData);

    // Compile the sprite shaders 
    main_shader.Compile(VERT_SHADER, FRAG_SHADER);
}


