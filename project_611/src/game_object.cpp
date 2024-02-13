#include "../header/game_object.h"

GameObject::GameObject(const std::string& name) : name { name } {}

void GameObject::Render() {
	p_sprite->render();
}

void GameObject::Animate(const float elapsedTime) {}