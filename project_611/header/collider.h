#ifndef COLLIDER_H
#define COLLIDER_H

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

#include "glm.hpp"
#include "game_object.h"
#include "environment_object.h"

class Collider {
public:
	Collider() = default;
	~Collider() = default;

	void checkCollision(const std::map<std::string, GameObject*>& animatedObjects, const std::map<std::string, EnvironmentObject*>& staticObjects);

private:
	bool detectCollision(const glm::vec2& pos1, const glm::vec2& pos2);
	bool detectCollisionX(const glm::vec2& pos1, const glm::vec2& pos2);
	bool detectCollisionY(const glm::vec2& pos1, const glm::vec2& pos2);

	// collision between an actor and a solid object
	void bumpBackHorizontal(GameObject* smallObject, EnvironmentObject* largeObject);
	// collision between an actor and a solid object
	void bumpBackVertical(GameObject* smallObject, EnvironmentObject* largeObject);
};

#endif