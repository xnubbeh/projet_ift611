#ifndef MONSTER_H
#define MONSTER_H

#include "game_object.h"

class Monster : GameObject
{

public:
	Monster(const std::string& name) : GameObject{ name } {};
	~Monster() = default;
	

private:
	// private car les objets DOIVENT avoir un nom
	Monster() = default;


};

#endif