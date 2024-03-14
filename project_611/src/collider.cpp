#include "../header/collider.h"

void Collider::checkCollision(const std::map<std::string, GameObject*>& gameMap, const std::map<std::string, EnvironmentObject*>& environmentMap) {
	
}

bool Collider::detectCollision(glm::vec2 pos1, glm::vec2 pos2) {
	if (pos1.y < pos2.y) {
		//if pos1 is inside pos2 there is a collision
		return true;
	}
	return false;
}