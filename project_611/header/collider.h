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
	Collider() { std::cout << "COLLIDER CREATED" << std::endl; }
	~Collider() = default;

	void checkCollision(const std::map<std::string, GameObject*>& animatedObjects, const std::map<std::string, EnvironmentObject*>& staticObjects);

private:
	bool detectCollision(const glm::vec2& pos1, const glm::vec2& pos2);
	bool detectCollisionX(const glm::vec2& pos1, const glm::vec2& pos2);
	bool detectCollisionY(const glm::vec2& pos1, const glm::vec2& pos2);

	// this is the result of a collision where a smaller mass collides with an infinite mass (immovable object)
	// the return value is the displacement to give the smaller object so that it does not collide with the first object
	void bumpBack(GameObject* smallObject, EnvironmentObject* largeObject);

};

#endif