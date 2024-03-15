#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"



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
		speed{ speed },
		direction{ Direction::Right },
		status{ Status::Idle },
		statusHasChanged{ false },
		indexInFlipBook{ 0 }
		{};

	~Player() = default;
	void Animate(const float elapsedTime) override;

private:
	// private cstor car les objets DOIVENT avoir un nom
	Player() = default;
	
	// private methods
	void Move();
	void AnimateSprite(const float elapsedTime);
	void MakeFaceDirection(Direction direction);

	// private attributes
	float speed;
	glm::vec2 velocity{};
	Direction direction;
	Status status;
	bool statusHasChanged;
	int indexInFlipBook;
};

#endif