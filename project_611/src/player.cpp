#include "../header/player.h"
#include "../header/input_manager.h"
#include "../header/sprite_index.h"

#include <iostream>

#define MAXIMUM_FRAME_DISPLAY_DURATION 32.0f

void Player::Animate(const float elapsedTime) {
	Move();
	AnimateSprite(elapsedTime);
}

void Player::Move() {
	Status previousStatus = status;
	Direction previousDirection = direction;
	velocity = glm::vec2{};
	
	//sideways
	if (InputManager::getInstance()->pressedKey[Key::A] && !InputManager::getInstance()->pressedKey[Key::D]) {
		velocity += glm::vec2(-1, 0);
		direction = Direction::Left;
		status = Status::Walking;
	}
	else if (InputManager::getInstance()->pressedKey[Key::D] && !InputManager::getInstance()->pressedKey[Key::A]) {
		velocity += glm::vec2(1, 0);
		direction = Direction::Right;
		status = Status::Walking;
	}
	else {
		status = Status::Idle;
	}

	//up and down
	if (InputManager::getInstance()->pressedKey[Key::W] && !InputManager::getInstance()->pressedKey[Key::S]) {
		velocity += glm::vec2(0, 1);
	}
	else if (InputManager::getInstance()->pressedKey[Key::S] && !InputManager::getInstance()->pressedKey[Key::W]) {
		velocity += glm::vec2(0, -1);
	}

	if (direction != previousDirection) {
		MakeFaceDirection(direction);
	}

	translate(velocity * speed);
	statusHasChanged = previousStatus != status;
}

void Player::MakeFaceDirection(Direction direction) {
	int directionValue = direction == Direction::Left ? LEFT : RIGHT;
	std::cout << directionValue<<"\n";
	if (spriteIndex != NO_SPRITE) {
		Sprite::getInstance()->setSpriteDirectionAt(spriteIndex, directionValue);
		renderData.direction = directionValue;
	}
}

void Player::AnimateSprite(const float elapsedTime) {
	static float elapsedTimeSinceLastSpriteSwitch{ 0 };
	// reset the animation if the status has changed
	if (statusHasChanged) {
		indexInFlipBook = 0;
		elapsedTimeSinceLastSpriteSwitch = 0;
	}
	else {
		elapsedTimeSinceLastSpriteSwitch += elapsedTime;
	}
	if (elapsedTimeSinceLastSpriteSwitch == 0 || elapsedTimeSinceLastSpriteSwitch > MAXIMUM_FRAME_DISPLAY_DURATION) {
		glm::vec2 spriteOffset;

		switch (status) {
		case Status::Walking: {
			indexInFlipBook = (indexInFlipBook + 1) % PLAYER_WALKING_NUM_SPRITES;
			spriteOffset = SpriteIndex::getInstance()->getSpriteOffset(SpriteType::PlayerWalking, indexInFlipBook);
			break;
		}
		case Status::Jumping: {
			indexInFlipBook = (indexInFlipBook + 1) % PLAYER_JUMPING_NUM_SPRITES;
			spriteOffset = SpriteIndex::getInstance()->getSpriteOffset(SpriteType::PlayerJumping, indexInFlipBook);
			break;
		}
		case Status::Idle: {
			indexInFlipBook = (indexInFlipBook + 1) % PLAYER_IDLE_NUM_SPRITES;
			spriteOffset = SpriteIndex::getInstance()->getSpriteOffset(SpriteType::PlayerJumping, indexInFlipBook);
			break;
		}
		}

		changeSpriteFrame(std::move(spriteOffset));
	}
}
