#include "../header/collider.h"

#define TEST 50

void Collider::checkCollision(const std::map<std::string, GameObject*>& gameMap, const std::map<std::string, EnvironmentObject*>& environmentMap) {
	//algo naif
	for (auto const& gameCoord : gameMap) {
		//backup gamecoord
		for (auto const& environmentCoord : environmentMap) {
			if (detectCollision(gameCoord.second->getPosition(), environmentCoord.second->getPosition())) {
				std::cout << "COLLIDED" << std::endl;
				//oh shit faut loader le back up pcq on est dans le mur
			}
		}
	}
}

bool Collider::detectCollision(glm::vec2 pos1, glm::vec2 pos2) {
	return pos1.x < pos2.x + TEST && // Collision on Left of a and right of b
		pos1.x + TEST > pos2.x && // Collision on Right of a and left of b
		pos1.y < pos2.y + TEST && // Collision on Bottom of a and Top of b
		pos1.y + TEST > pos2.y;    // Collision on Top of a and Bottom of b
	//return a.pos.x < b.pos.x  + b.size.x && // Collision on Left of a and right of b
	//a.pos.x + a.size.x > b.pos.x && // Collision on Right of a and left of b
	//	a.pos.y < b.pos.y + b.size.y && // Collision on Bottom of a and Top of b
	//	a.pos.y + a.size.y > b.pos.y;    // Collision on Top of a and Bottom of b
}