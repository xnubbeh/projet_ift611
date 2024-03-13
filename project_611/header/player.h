#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

enum class Status {
	Idle,
	WalkingLeft,
	WalkingRight,
	JumpingStraighUp,
	JumpingRight,
	JumpingLeft
};

class Player : public GameObject
{
public:
	Player(const std::string& name, float speed) : GameObject{ name }, velocity{ speed }, status {Status::Idle} {};
	~Player() = default;
	void Animate(const float elapsedTime) override;

private:
	// private cstor car les objets DOIVENT avoir un nom
	Player() = default;
	
	// private methods
	void Move();
	void AnimateSprite(const float elapsedTime);

	// private attributes
	float velocity;
	Status status;

};

#endif