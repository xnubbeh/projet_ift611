#include "../header/player.h"
#include "../header/input_manager.h"
#include "../header/sprite_index.h"

#include <iostream>

#define MAXIMUM_FRAME_DISPLAY_DURATION 32.0f // about 2 frames

void Player::Animate(const float elapsedTime) {
	Move();
	AnimateSprite(elapsedTime);
}

void Player::Move() {
	Status previousStatus = status;
	Direction previousDirection = direction;

	velocity = glm::vec2{};

	if (grounded) {
		//sideways
		if (InputManager::getInstance()->pressedKey[Key::A] && !InputManager::getInstance()->pressedKey[Key::D]) {
			horizontalVelocity = -1.0f;
			direction = Direction::Left;
			status = Status::Walking;
		}
		else if (InputManager::getInstance()->pressedKey[Key::D] && !InputManager::getInstance()->pressedKey[Key::A]) {
			horizontalVelocity = 1.0f;
			direction = Direction::Right;
			status = Status::Walking;
		}
		else {
			status = Status::Idle;
		}

		//up and down
		if (InputManager::getInstance()->pressedKey[Key::SPACE]) {
			Jump();
		}
		//else if (InputManager::getInstance()->pressedKey[Key::S] && !InputManager::getInstance()->pressedKey[Key::W]) {
		//	velocity += glm::vec2(0, -1);
		//}
	}
	

	if (direction != previousDirection) {
		MakeFaceDirection(direction);
	}

	Gravity();
	velocity = glm::vec2(horizontalVelocity * horizontalSpeed, verticalVelocity);

	translate(velocity);
	statusHasChanged = previousStatus != status;
}

void Player::MakeFaceDirection(Direction direction) {
	int directionValue = direction == Direction::Left ? LEFT : RIGHT;
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
			spriteOffset = SpriteIndex::getInstance()->getSpriteOffset(SpriteType::PlayerIdle, indexInFlipBook);
			break;
		}
		}

		changeSpriteFrame(std::move(spriteOffset));
	}
}

void Player::Gravity() {
	verticalVelocity -= GRAVITATIONAL_ACCELERATION;
	if (verticalVelocity < TERMINAL_VELOCITY) {
		verticalVelocity = TERMINAL_VELOCITY;
	}

	velocity.y = verticalVelocity;
}

void Player::Jump() {
	if (grounded) {
		grounded = false;
		verticalVelocity = 16.0f;
	}
}

