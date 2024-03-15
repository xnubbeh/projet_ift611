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
	~Collider();

	void checkCollision(const std::map<std::string, GameObject*>& gameMap, const std::map<std::string, EnvironmentObject*>& environmentMap);

private:
	bool detectCollision(glm::vec2 pos1, glm::vec2 pos2);
	bool detectCollisionX(glm::vec2 pos1, glm::vec2 pos2);
	bool detectCollisionY(glm::vec2 pos1, glm::vec2 pos2);
};

#endif