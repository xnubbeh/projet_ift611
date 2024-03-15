#include "../header/collider.h"

#define TEST 50 //this is suppose to be the size of the objet 

void Collider::checkCollision(const std::map<std::string, GameObject*>& gameMap, const std::map<std::string, EnvironmentObject*>& environmentMap) {
	//algo naif
	for (auto const& gameCoord : gameMap) {
		//backup gamecoord
		for (auto const& environmentCoord : environmentMap) {
			if(detectCollision(gameCoord.second->getPosition(), environmentCoord.second->getPosition())) {
				//std::cout << "POS1:    " << gameCoord.second->getPosition().x << "   " << environmentCoord.second->getPosition().y << std::endl;
				//std::cout << "POS2:    " << gameCoord.second->getPosition().x << "   " << environmentCoord.second->getPosition().y << std::endl;
				//std::cout << "COLLIDED" << std::endl;
				//oh shit faut loader le back up pcq on est dans le mur
			}
		}
	}
}

bool Collider::detectCollision(glm::vec2 pos1, glm::vec2 pos2) {
	
	if (detectCollisionY(pos1, pos2) && (detectCollisionX(pos1, pos2))) {
		std::cout << "COLLISION" << std::endl;
		return true;
	}
	return false;
}

bool Collider::detectCollisionX(glm::vec2 pos1, glm::vec2 pos2) {
	return pos1.x < pos2.x + TEST && // Collision on Left of pos1 and right of pos2
		   pos1.x + TEST > pos2.x;   // Collision on Right of pos1 and left of pos2
}

bool Collider::detectCollisionY(glm::vec2 pos1, glm::vec2 pos2) {
	return pos1.y + TEST > pos2.y &&      // Collision on Top of pos1 and Bottom of pos2
		   pos1.y < pos2.y + TEST;
}

/*
* =--------
* | pos1 
* |
* |
* |
* =--------
*/