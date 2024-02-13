#include "../header/game_object.h"

GameObject::GameObject(const std::string& name) : name { name } {}

void GameObject::Render() {
	// TODO FONCTION DESUETTE
	// p_sprite->Render(p_frame);
}

void GameObject::Animate(const float elapsedTime) {}


void GameObject::CreateRenderData(const RenderData& data) {
	sprite = data;
}

RenderData& GameObject::GetRenderData() {
	return sprite;
}