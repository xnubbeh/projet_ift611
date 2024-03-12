#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class Player : public GameObject
{

public:
	Player(const std::string& name, float speed) : GameObject{ name }, speed {speed} {};
	~Player() = default;
	void Animate(const float elapsedTime) override;


private:
	// private cstor car les objets DOIVENT avoir un nom
	Player() = default;
	
	// private methods
	void Move();
	void AnimateSprite(const float elapsedTime);

	// private attributes
	float speed;

};

#endif