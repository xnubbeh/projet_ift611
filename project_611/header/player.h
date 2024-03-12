#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class Player : GameObject
{

public:
	Player(const std::string& name) : GameObject{ name } {};
	~Player() = default;

private:
	// private car les objets DOIVENT avoir un nom
	Player() = default;

};

#endif