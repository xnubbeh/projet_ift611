#include "../header/player.h"
#include "../header/input_manager.h"

#include <iostream>
void Player::Animate(const float elapsedTime) {
	Move();
	AnimateSprite(elapsedTime);
}

void Player::Move() {
	//sideways
	if (InputManager::getInstance()->pressedKey[Key::A] && !InputManager::getInstance()->pressedKey[Key::D]) {
		translate(glm::vec2(-1, 0) * velocity);
	}
	else if (InputManager::getInstance()->pressedKey[Key::D] && !InputManager::getInstance()->pressedKey[Key::A]) {
		translate(glm::vec2(1, 0) * velocity);
	}

	//up and down
	if (InputManager::getInstance()->pressedKey[Key::W] && !InputManager::getInstance()->pressedKey[Key::S]) {
		translate(glm::vec2(0, 1) * velocity);
	}
	else if (InputManager::getInstance()->pressedKey[Key::S] && !InputManager::getInstance()->pressedKey[Key::W]) {
		translate(glm::vec2(0, -1) * velocity);
	}
}

void Player::AnimateSprite(const float elapsedTime) {

}
