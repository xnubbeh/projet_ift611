#include <algorithm>
#include <cmath>
#include "../header/collider.h"
#include "../header/player.h"



void Collider::checkCollision(const std::vector<GameObject*>& animatedObjects, const std::vector<EnvironmentObject*>& staticObjects) {
	std::for_each(begin(animatedObjects), end(animatedObjects), [&](GameObject* animatedObject) {
		std::for_each(begin(staticObjects), end(staticObjects), [&](EnvironmentObject* staticObject) {
			if (detectCollision(animatedObject, staticObject)) {
				bumpBackHorizontal(animatedObject, staticObject);
				bumpBackVertical(animatedObject, staticObject);
			}
			});
		});
}

bool Collider::detectCollision(const GameObject* obj1, const GameObject* obj2)
{
	glm::vec2 Pos1 = obj1->getHitboxOffset() + obj1->getPosition();
	glm::vec2 Pos2 = obj2->getHitboxOffset() + obj2->getPosition();


	bool collisionX = Pos1.x < Pos2.x + obj2->getHitboxDim().x && // Left side of obj1 with right side of obj2
					  Pos1.x + obj1->getHitboxDim().x > Pos2.x;   // Right side of obj1 with left side of obj2

	bool collisionY = Pos1.y + obj1->getHitboxDim().y > Pos2.y && // Top of obj1 with bottom of obj2
					  Pos1.y < Pos2.y + obj2->getHitboxDim().y;   // Bottom of obj1 with top of obj2
	
	

	return collisionX && collisionY;
}

void Collider::bumpBackHorizontal(GameObject* smallObject, EnvironmentObject* largeObject) {
	
	// Minimum translation vector resolution of the collision
	glm::vec2 smallObjectPos = smallObject->getPosition() + smallObject->getHitboxOffset();
	glm::vec2 largeObjectPos = largeObject->getPosition() + largeObject->getHitboxOffset();

	float overlapX;
	if (smallObjectPos.x < largeObjectPos.x) {
		overlapX = (smallObjectPos.x + smallObject->getHitboxDim().x) - largeObjectPos.x;
	}
	else {
		overlapX = (largeObjectPos.x + largeObject->getHitboxDim().x) - smallObjectPos.x;
	}

	float overlapY;
	if (smallObjectPos.y < largeObjectPos.y) {
		overlapY = (smallObjectPos.y + smallObject->getHitboxDim().y) - largeObjectPos.y;
	}
	else {
		overlapY = (largeObjectPos.y + largeObject->getHitboxDim().y) - smallObjectPos.y;
	}

	overlapX = overlapX < overlapY ? overlapX : 0;
	float xDirection = smallObjectPos.x < largeObjectPos.x ? -1.0 : 1.0;
	smallObject->translate(glm::vec2{ overlapX * xDirection, 0 });
}

void Collider::bumpBackVertical(GameObject* smallObject, EnvironmentObject* largeObject) {

	// Minimum translation vector resolution of the collision
	glm::vec2 smallObjectPos = smallObject->getPosition() + smallObject->getHitboxOffset();
	glm::vec2 largeObjectPos = largeObject->getPosition() + largeObject->getHitboxOffset();

	// Calculate vertical overlap
	float overlapX;
	if (smallObjectPos.x < largeObjectPos.x) {
		overlapX = (smallObjectPos.x + smallObject->getHitboxDim().x) - largeObjectPos.x;
	}
	else {
		overlapX = (largeObjectPos.x + largeObject->getHitboxDim().x) - smallObjectPos.x;
	}

	float overlapY;
	if (smallObjectPos.y < largeObjectPos.y) {
		overlapY = (smallObjectPos.y + smallObject->getHitboxDim().y) - largeObjectPos.y;
	}
	else {
		overlapY = (largeObjectPos.y + largeObject->getHitboxDim().y) - smallObjectPos.y;
	}

	overlapY = overlapX < overlapY ? 0 : overlapY;

	// Determine direction of bump back
	float yDirection = smallObjectPos.y < largeObjectPos.y ? -1.0 : 1.0;

	// Apply vertical bump back based on overlap
	smallObject->translate(glm::vec2{ 0, overlapY * yDirection });

	// Adjust grounded state as necessary
	if (yDirection > 0) { // Only ground if the player is above the object (floor)
		static_cast<Player*>(smallObject)->Ground(largeObject->IsGround() && overlapY > 0);
	}
}