#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

#define TERMINAL_VELOCITY -14.0f
#define GRAVITATIONAL_ACCELERATION 1.0f

class Player : public GameObject
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
	Player(const std::string& name, float speed) :
		GameObject{ name },
		horizontalSpeed{ speed+6.0f },
		verticalSpeed{ speed+7.0f }, // TODO this should be handled by gravity I guess
		horizontalVelocity{0},
		verticalVelocity{0},
		direction{ Direction::Right },
		status{ Status::Idle },
		statusHasChanged{ false },
		grounded{false},
		indexInFlipBook{ 0 }
		{};

	~Player() = default;
	void Animate(const float elapsedTime) override;
	bool isGrounded() { return grounded; }
	void Ground() { grounded = true;}

private:
	// private cstor car les objets DOIVENT avoir un nom
	Player() = default;
	
	// private methods
	void Move();
	void AnimateSprite(const float elapsedTime);
	void MakeFaceDirection(Direction direction);
	void Gravity();
	void Jump();

	// private attributes
	float horizontalSpeed;
	float verticalSpeed;
	float horizontalVelocity;
	float verticalVelocity;
	glm::vec2 velocity{};
	Direction direction;
	Status status;
	bool statusHasChanged;
	bool grounded;
	int indexInFlipBook;
};

#endif