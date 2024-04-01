#ifndef MONSTER_H
#define MONSTER_H

#include "game_object.h"

#define TERMINAL_VELOCITY -14.0f
#define GRAVITATIONAL_ACCELERATION 1.0f

class Monster : public GameObject
{
	enum class Direction {
		Left,
		Right
	};

	enum class Status {
		Idle,
		Walking,
		Jumping
	};

public:
	Monster(const std::string& name, float speed, float initialDirection, unsigned int loopLength) : 
		GameObject{ name },
		horizontalVelocity{ speed + 6.0f },
		horizontalDirection{ initialDirection },
		verticalVelocity{ 0 }, 
		direction{ Direction::Right },
		status{ Status::Idle },
		statusHasChanged{ false },
		grounded{ false },
		indexInFlipBook{ 0 },
		elapsedFrames{ 0 },
		loopLength{ loopLength }
		{};
	~Monster() = default;
	void Animate(const float elapsedTime) override;
	bool isGrounded() { return grounded; }
	void Ground(bool resetVerticalVelocity);
	

private:
	// private car les objets DOIVENT avoir un nom
	Monster() = default;

	// private methods
	void Move(unsigned int loopLength);
	void AnimateSprite(const float elapsedTime);
	void MakeFaceDirection(Direction direction);
	void Gravity();
	void Jump();

	//private attributes
	float horizontalVelocity;
	float horizontalDirection;
	float verticalVelocity;
	float elapsedTimeSinceLastJump;
	glm::vec2 velocity{};
	Direction direction;
	Status status;
	bool statusHasChanged;
	bool grounded;
	int indexInFlipBook;
	unsigned long int elapsedFrames;
	unsigned int loopLength;


};

#endif