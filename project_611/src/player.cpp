#include "../header/player.h"
#include "../header/input_manager.h"

#include <iostream>
void Player::Animate(const float elapsedTime) {
	Move();
	AnimateSprite(elapsedTime);
}

void Player::Move() {
	//sideways
	if (InputManager::getInstance()->pressedKey[Key::A]) {
		translate(glm::vec2(-1, 0) * speed);
		std::cout << getPosition().x << "    " << getPosition().y << std::endl;
	}
	else if (InputManager::getInstance()->pressedKey[Key::D]) {
		translate(glm::vec2(1, 0) * speed);
		std::cout << getPosition().x << "    " << getPosition().y << std::endl;
	}

	//up and down
	if (InputManager::getInstance()->pressedKey[Key::W]) {
		translate(glm::vec2(0, 1) * speed);
		std::cout << getPosition().x << "    " << getPosition().y << std::endl;
	}
	else if (InputManager::getInstance()->pressedKey[Key::S]) {
		translate(glm::vec2(0, -1) * speed);
		std::cout << getPosition().x << "    " << getPosition().y << std::endl;
	}

	
}

void Player::AnimateSprite(const float elapsedTime) {

}
