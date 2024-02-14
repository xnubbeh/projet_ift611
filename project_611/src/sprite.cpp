#include "../header/sprite.h"
#include "../header/camera.h"

Sprite::Sprite() :
    main_shader { MAIN_SHADER_NAME },
    sprite_sheet {TEXTURE_PATH}

{}

Sprite::~Sprite() {
    // TODO
 //   glDeleteVertexArrays(1, &this->quadVAO);
}

void Sprite::Render(Frame* frame_pointer) {
    //shader.Bind();
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //shader.Release();
}

//void Sprite::initRenderData() {
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
//}

void Sprite::RenderAll()
{
    // on a un array de *sprites* qu'on veut render
    // le buffer qu'on passe contient un array de structs
        // chaque struct contient le data pour render une sprite individuelle
    
    main_shader.SetMatrix4("orthoProjection", Camera::getInstance()->Projection(), main_shader.vertexShaderProgram);

   // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(RenderData) * numSprites, renderData);
    // MAYBE : THIS SHOULD NOT BE SYSTEMATICALLY CALLED EVERY FRAME
    {
        glNamedBufferSubData(VBO_POSITION, 0, sizeof(glm::vec4) * numSprites, positionOffset_size);
        glNamedBufferSubData(VBO_SPRITE, 0, sizeof(glm::ivec4) * numSprites, atlasOffset_spriteSize);
        glNamedBufferSubData(VBO_DEPTH, 0, sizeof(float) * numSprites, zBuffer);
    }

    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, numSprites);
}


int Sprite::AddSprite(const RenderData& data) {

    positionOffset_size [numSprites] = glm::vec4{ data.pos, data.size };
    atlasOffset_spriteSize [numSprites] = glm::vec4{data.atlasOffset, data.spriteSize};
    zBuffer [numSprites] = data.z;

    ++numSprites;
    return numSprites - 1;
}

void Sprite::Init() {

    InitBuffers();

    // Compile the sprite shaders 
    main_shader.Compile(VERT_SHADER, FRAG_SHADER);

    // Set background color
    glClearColor(0.5, 0.5, 0.5, 1.0);
}

void Sprite::InitBuffers() {

    // Must be done or else nothing renders
    glCreateVertexArrays(1, &VAO);
    glEnableVertexArrayAttrib(VAO, 0);
    glBindVertexArray(VAO);

    // Position offset and size channel 1 (pass a vec4 that we will decompose as 2 vec2)
    glCreateBuffers(1, &VBO_POSITION);
    glNamedBufferData(VBO_POSITION, sizeof(glm::vec4) * MAX_SPRITES, positionOffset_size, GL_DYNAMIC_DRAW);
    glEnableVertexArrayAttrib(VAO, 1);
    glVertexArrayAttribFormat(VAO, 1, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(VAO, 1, VBO_POSITION, 0, sizeof(glm::vec4));
    glVertexArrayAttribBinding(VAO, 1, 1);
    glVertexAttribDivisor(1, 1);

    // Atlas offset and sprite size channel 2 (pass a ivec4 that we will decompose as 2 ivec2)
    glCreateBuffers(1, &VBO_SPRITE);
    glNamedBufferData(VBO_SPRITE, sizeof(glm::ivec4) * MAX_SPRITES, atlasOffset_spriteSize, GL_DYNAMIC_DRAW);
    glEnableVertexArrayAttrib(VAO, 2);
    glVertexArrayAttribFormat(VAO, 2, 4, GL_INT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(VAO, 2, VBO_SPRITE, 0, sizeof(glm::ivec4));
    glVertexArrayAttribBinding(VAO, 2, 2);
    glVertexAttribDivisor(2, 1);

    // Depth channel 3 (pass one float)
    glCreateBuffers(1, &VBO_DEPTH);
    glNamedBufferData(VBO_DEPTH, sizeof(float) * MAX_SPRITES, zBuffer, GL_DYNAMIC_DRAW);
    glEnableVertexArrayAttrib(VAO, 3);
    glVertexArrayAttribFormat(VAO, 3, 1, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(VAO, 3, VBO_DEPTH, 0, sizeof(float));
    glVertexArrayAttribBinding(VAO, 3, 3);
    glVertexAttribDivisor(3, 1);

}


