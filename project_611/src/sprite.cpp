#include "../header/sprite.h"
#include "../header/camera.h"

Sprite::Sprite() :
    main_shader { MAIN_SHADER_NAME },
    sprite_sheet {TEXTURE_PATH}

{}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VBO_POSITION);
    glDeleteVertexArrays(1, &VBO_SPRITE);
    glDeleteVertexArrays(1, &VBO_DEPTH);
}

void Sprite::RenderAll()
{
    // this is here in case the camera ever moves
    main_shader.SetMatrix4("orthoProjection", Camera::getInstance()->Projection(), main_shader.VertexShader());

    // update buffers
    glNamedBufferSubData(VBO_POSITION, 0, sizeof(glm::vec4) * numSprites, positionOffset_size);
    glNamedBufferSubData(VBO_SPRITE, 0, sizeof(glm::ivec4) * numSprites, atlasOffset_spriteSize);
    glNamedBufferSubData(VBO_DEPTH, 0, sizeof(float) * numSprites, zBuffer);

    // one draw call to rule them all
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

    // This must be done or else nothing renders
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
    glNamedBufferData(VBO_SPRITE, sizeof(glm::vec4) * MAX_SPRITES, atlasOffset_spriteSize, GL_DYNAMIC_DRAW);
    glEnableVertexArrayAttrib(VAO, 2);
    glVertexArrayAttribFormat(VAO, 2, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(VAO, 2, VBO_SPRITE, 0, sizeof(glm::vec4));
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


