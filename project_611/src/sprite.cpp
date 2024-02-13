#include "../header/sprite.h"

Sprite::Sprite(ShaderPipeline& shader) {
	this->shader = shader;
	this->initRenderData();
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void Sprite::DrawSprite(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
    // prepare transformations
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    //model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    //model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    //model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    //model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    //this->shader.SetMatrix4("model", model, shader.vs);

    //// render textured quad
    //this->shader.SetVector3f("spriteColor", color, shader.vs);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

  //  glBindVertexArray(this->quadVAO);

  //  glBindVertexArray(0);
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

