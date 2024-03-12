#include "../header/game_object.h"

GameObject::GameObject(const std::string& name) :
	name { name },
	spriteIndex { NO_SPRITE }
{}

void GameObject::Render() {
	// TODO FONCTION DESUETTE
	// p_sprite->Render(p_frame);
}

void GameObject::Animate(const float elapsedTime) {}


void GameObject::CreateRenderData(const RenderData& data) {
	sprite = data;
	spriteIndex = Sprite::getInstance()->AddSprite(sprite);
}

RenderData& GameObject::GetRenderData() {
	return sprite;
}

void GameObject::translate(const glm::vec2& translation)
{
	if (spriteIndex != NO_SPRITE) {
		Sprite::getInstance()->translateSpriteAt(spriteIndex, translation);
	}
}

void GameObject::changeSpriteFrame(const glm::vec2& newSpriteAtlasPosition) {
	if (spriteIndex != NO_SPRITE) {
		Sprite::getInstance()->changeSpriteModelAt(spriteIndex, newSpriteAtlasPosition);
	}
}
