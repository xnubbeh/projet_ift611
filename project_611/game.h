#pragma once

#include <glad/glad.h>
#include <glfw3.h>

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_DEAD
};

class Game
{
public:
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;
	
	Game(unsigned int, unsigned int);
	~Game();

	void Init();

	void ProcessInput(float);
	void Update(float);
	void Render();

};

