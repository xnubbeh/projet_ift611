#include "../header/monster.h"
#include "../header/sprite_index.h"
#include <iostream>

#define MINIMUM_TIME_BEFORE_NEXT_JUMP 512.0f

void Monster::Animate(const float elapsedTime) {
	Move();
	AnimateSprite(elapsedFrames);
	elapsedTimeSinceLastJump += elapsedTime;
	++elapsedFrames;
}

void Monster::Move() {
	Status previousStatus = status;
	Direction previousDirection = direction;

	velocity = glm::vec2{};

	Gravity();
	velocity = glm::vec2(horizontalDirection * horizontalVelocity, verticalVelocity);

	translate(velocity);
	statusHasChanged = previousStatus != status;
}

void Monster::MakeFaceDirection(Direction direction) {
	int directionValue = direction == Direction::Left ? LEFT : RIGHT;
	if (spriteIndex != NO_SPRITE) {
		Sprite::getInstance()->setSpriteDirectionAt(spriteIndex, directionValue);
		renderData.direction = directionValue;
	}
}

void Monster::AnimateSprite(const float elapsedTime) {
	// reset the animation if the status has changed
	if (statusHasChanged) {
		indexInFlipBook = 0;
	}
	if (elapsedFrames % 3 == 0) {
		glm::vec2 spriteOffset;
		//since the monster has no animations he just stays in 1 sprite
		switch (status) {
		case Status::Walking: {
			indexInFlipBook = (indexInFlipBook + 1) % MONSTER_WALKING_NUM_SPRITES;
			spriteOffset = SpriteIndex::getInstance()->getSpriteOffset(SpriteType::MonsterWalking, indexInFlipBook);
			break;
		}
		case Status::Jumping: {
			indexInFlipBook = (indexInFlipBook + 1) % MONSTER_WALKING_NUM_SPRITES;
			spriteOffset = SpriteIndex::getInstance()->getSpriteOffset(SpriteType::MonsterWalking, indexInFlipBook);
			break;
		}
		case Status::Idle: {
			indexInFlipBook = (indexInFlipBook + 1) % MONSTER_WALKING_NUM_SPRITES;
			spriteOffset = SpriteIndex::getInstance()->getSpriteOffset(SpriteType::MonsterWalking, indexInFlipBook);
			break;
		}
		}

		changeSpriteFrame(std::move(spriteOffset));
	}
}

void Monster::Gravity() {
	verticalVelocity -= GRAVITATIONAL_ACCELERATION;
	if (verticalVelocity < TERMINAL_VELOCITY) {
		verticalVelocity = TERMINAL_VELOCITY;
	}

	velocity.y = verticalVelocity;
}

void Monster::Jump() {
	if (grounded && elapsedTimeSinceLastJump > MINIMUM_TIME_BEFORE_NEXT_JUMP) {
		elapsedTimeSinceLastJump = 0.0f;
		grounded = false;
		verticalVelocity = 16.0f;
	}
}

void Monster::Ground(bool resetVerticalVelocity) {
	if (resetVerticalVelocity) {
		verticalVelocity = 0.0f;
	}

	grounded = true;
}