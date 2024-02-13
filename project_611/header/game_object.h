#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include "frame.h"
#include "sprite.h"

class GameObject
{

public:
	GameObject(const std::string& name);
	~GameObject() = default;
	
	void Render();
	void Animate(const float elapsedTime);

private:
	// private car les objets DOIVENT avoir un nom
	GameObject() = default;
	std::string name;

	Frame* p_frame;
	Sprite* p_sprite;



};

#endif