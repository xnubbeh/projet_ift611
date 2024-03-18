#include <cmath>
#include "../header/collider.h"
#include "../header/player.h"

#define TEST 50 // TODO : figure a better way to do get the collision boxes of objects

void Collider::checkCollision(const std::map<std::string, GameObject*>& animatedObjects, const std::map<std::string, EnvironmentObject*>& staticObjects) {
	for (std::pair<std::string, GameObject*> animatedObject : animatedObjects) {
		// iterate through the scene's static objects for collisions
		// this could be refined if performances are affected


		for (std::pair<std::string, EnvironmentObject*> environmentObject : staticObjects) {
			if (detectCollision(animatedObject.second->getPosition(), environmentObject.second->getPosition())) {
				bumpBackVertical(animatedObject.second, environmentObject.second);
			}
		}

		// Il est nécessaire de répéter cette boucle deux fois p
		for (std::pair<std::string, EnvironmentObject*> environmentObject : staticObjects) {
			if (detectCollision(animatedObject.second->getPosition(), environmentObject.second->getPosition())) {
				bumpBackHorizontal(animatedObject.second, environmentObject.second);
			}
		}

		// TODO : we should probably iterate through other animated objects as well 
	}
}

bool Collider::detectCollision(const glm::vec2& pos1, const glm::vec2& pos2) {
	return detectCollisionY(pos1, pos2) && (detectCollisionX(pos1, pos2));
}

bool Collider::detectCollisionX(const glm::vec2& pos1, const glm::vec2& pos2) {
	return pos1.x < pos2.x + TEST && // Collision on Left of pos1 and right of pos2
		   pos1.x + TEST > pos2.x;   // Collision on Right of pos1 and left of pos2
}

bool Collider::detectCollisionY(const glm::vec2& pos1, const glm::vec2& pos2) {
	return pos1.y + TEST > pos2.y &&      // Collision on Top of pos1 and Bottom of pos2
		   pos1.y < pos2.y + TEST;
}

void Collider::bumpBackHorizontal(GameObject* smallObject, EnvironmentObject* largeObject) {
	
	// Minimum translation vector resolution of the collision
	glm::vec2 smallObjectPos = smallObject->getPosition();
	glm::vec2 largeObjectPos = largeObject->getPosition();

	float dX = (smallObjectPos.x < largeObjectPos.x) ?
		(smallObjectPos.x + TEST) - (largeObjectPos.x) :
		(largeObjectPos.x + TEST) - (smallObjectPos.x);
	float dY = (smallObjectPos.y < largeObjectPos.y) ?
		(smallObjectPos.y + TEST) - (largeObjectPos.y) :
		(largeObjectPos.y + TEST) - (smallObjectPos.y);

	float bumpBackX = dX < dY ? dX : 0;

	float xDirection = smallObjectPos.x < largeObjectPos.x ? -1.0 : 1.0;

	smallObject->translate(glm::vec2{ bumpBackX * xDirection, 0 });
}

void Collider::bumpBackVertical(GameObject* smallObject, EnvironmentObject* largeObject) {

	// Minimum translation vector resolution of the collision
	glm::vec2 smallObjectPos = smallObject->getPosition();
	glm::vec2 largeObjectPos = largeObject->getPosition();

	float dX = (smallObjectPos.x < largeObjectPos.x) ?
		(smallObjectPos.x + TEST) - (largeObjectPos.x) :
		(largeObjectPos.x + TEST) - (smallObjectPos.x);
	float dY = (smallObjectPos.y < largeObjectPos.y) ?
		(smallObjectPos.y + TEST) - (largeObjectPos.y) :
		(largeObjectPos.y + TEST) - (smallObjectPos.y);


	float bumpBackY = dX < dY ? 0 : dY;

	float yDirection = smallObjectPos.y < largeObjectPos.y ? -1.0 : 1.0;
	
	// TODO : MAKE GAME OBJECT A SUBCLASS OF ANIMATED OBJECT
	if (!static_cast<Player*>(smallObject)->isGrounded() && yDirection > 0) {
		static_cast<Player*>(smallObject)->Ground();
		std::cout << "PLAYED GROUNDED\n";
	}

	smallObject->translate(glm::vec2{ 0, bumpBackY * yDirection });
}