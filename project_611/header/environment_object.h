#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

#include "game_object.h"

class EnvironmentObject : GameObject
{

public:
	EnvironmentObject(const std::string& name) : GameObject{ name } {};
	~EnvironmentObject() = default;

private:
	// private car les objets DOIVENT avoir un nom
	EnvironmentObject() = default;



};

#endif