#include "../header/game_object.h"

GameObject::GameObject(const std::string& name) :
	name { name },
	spriteIndex { NO_SPRITE },
	collidable { false }
{}

void GameObject::Animate(const float elapsedTime) {}


void GameObject::CreateRenderData(const RenderData& data) {
	renderData = data;
	spriteIndex = Sprite::getInstance()->AddSprite(renderData);
}

RenderData& GameObject::GetRenderData() {
	return renderData;
}

void GameObject::translate(const glm::vec2& translation)
{
	if (spriteIndex != NO_SPRITE) {
		Sprite::getInstance()->translateSpriteAt(spriteIndex, translation);
		renderData.pos += translation;
	}
}

void GameObject::changeSpriteFrame(const glm::vec2& newSpriteAtlasPosition) {
	if (spriteIndex != NO_SPRITE) {
		Sprite::getInstance()->changeSpriteModelAt(spriteIndex, newSpriteAtlasPosition);
		renderData.atlasOffset = newSpriteAtlasPosition;
	}
}

glm::vec2 GameObject::getPosition() const {
	return renderData.pos;
}

void GameObject::setHitboxDim(const glm::vec2& dim)
{
	collidable = true;
	hitboxDim = dim;
}

void GameObject::setHitboxOffset(const glm::vec2& offset)
{
	hitboxOffset = offset;
}

glm::vec2 GameObject::getHitboxDim() const{
	return hitboxDim;
}

glm::vec2 GameObject::getHitboxOffset() const{
	return hitboxOffset;
}

bool GameObject::isCollidable() const {
	return collidable;
}