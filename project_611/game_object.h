#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>

class GameObject
{

public:
	GameObject(const std::string& name);
	~GameObject() = default;
	
	void Render();


private:
	// private car les objets DOIVENT avoir un nom
	GameObject() = default;
	std::string name;


};

#endif