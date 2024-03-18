#include "../header/player.h"
#include "../header/input_manager.h"
#include "../header/sprite_index.h"

#include <iostream>

#define MINIMUM_TIME_BEFORE_NEXT_JUMP 512.0f

void Player::Animate(const float elapsedTime) {
	Move();
	AnimateSprite(elapsedTime);
	elapsedTimeSinceLastJump += elapsedTime;
	++elapsedFrames;
}

void Player::Move() {
	Status previousStatus = status;
	Direction previousDirection = direction;

	velocity = glm::vec2{};


	//sideways
	if (InputManager::getInstance()->pressedKey[Key::A] && !InputManager::getInstance()->pressedKey[Key::D]) {
		horizontalDirection = -1.0f;
		direction = Direction::Left;
		status = Status::Walking;
	}
	else if (InputManager::getInstance()->pressedKey[Key::D] && !InputManager::getInstance()->pressedKey[Key::A]) {
		horizontalDirection = 1.0f;
		direction = Direction::Right;
		status = Status::Walking;
	}
	else {
		horizontalDirection = 0.0f;
		status = Status::Idle;
	}

	//up and down
	if (InputManager::getInstance()->pressedKey[Key::SPACE]) {
		Jump();
	}
	else {
		jumpButtonReleasedSinceLastJump = true;
	}
	//else if (InputManager::getInstance()->pressedKey[Key::S] && !InputManager::getInstance()->pressedKey[Key::W]) {
	//	velocity += glm::vec2(0, -1);
	//}

	

	if (direction != previousDirection) {
		MakeFaceDirection(direction);
	}

	Gravity();
	velocity = glm::vec2(horizontalDirection * horizontalVelocity, verticalVelocity);

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
	// reset the animation if the status has changed
	if (statusHasChanged) {
		indexInFlipBook = 0;
	}
	if (elapsedFrames%3 == 0) {
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
	if (grounded && elapsedTimeSinceLastJump > MINIMUM_TIME_BEFORE_NEXT_JUMP && jumpButtonReleasedSinceLastJump) {
		jumpButtonReleasedSinceLastJump = false;
		elapsedTimeSinceLastJump = 0.0f;
		grounded = false;
		verticalVelocity = 16.0f;
	}
}

