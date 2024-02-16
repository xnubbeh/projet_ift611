#include "../header/material.h"


Material::Material(std::string iName) : name { iName } {
	scene = Scene::getInstance();
	shaderPipeline = new ShaderPipeline{ iName };

    // TODO
    // NE PAS LOADER DE TEXTURE ICI 
    texture = new SpriteSheet{"../star.png"};
}



void Material::render(GameObject * o) {
    shaderPipeline->Bind();
    glActiveTexture(GL_TEXTURE0);
    texture->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    shaderPipeline->Release();
}

void Material::animate(GameObject* o, const float elapsedTime) {}