#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include "frame.h"
#include "sprite.h"

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
	glm::vec2 getPosition();

private:
	// private car les objets DOIVENT avoir un nom
	GameObject() = default;

protected:
	std::string name;

	Frame* p_frame;
	RenderData renderData;
	int spriteIndex;



};

#endif