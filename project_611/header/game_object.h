#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include "sprite.h"

#include "glm.hpp"

#define NO_SPRITE -1

class GameObject
{

public:
	GameObject(const std::string& name);
	virtual ~GameObject() = default;
	
	virtual void Animate(const float elapsedTime);

	void CreateRenderData(const RenderData& data);
	RenderData& GetRenderData();
	void translate(const glm::vec2& translation);
	void changeSpriteFrame(const glm::vec2& newSpriteAtlasPosition);
	glm::vec2 getPosition() const;

	void setHitboxDim(const glm::vec2& dim);
	void setHitboxOffset(const glm::vec2& offset);

	glm::vec2 getHitboxDim() const;
	glm::vec2 getHitboxOffset() const;

private:
	// private car les objets DOIVENT avoir un nom
	GameObject() = default;

protected:
	std::string name;

	RenderData renderData;
	int spriteIndex;

	glm::vec2 hitboxDim{};
	glm::vec2 hitboxOffset{};
	



};

#endif