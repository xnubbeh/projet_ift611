
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

//#include <glad/glad.h>
//#include <glfw3.h>
#include <iostream>

#include "game.h"
#include "resource_manager.h"
#include "scene.h"

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

class GameEngine
{
	enum GameState {
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN,
		GAME_DEAD
	};

public:
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;
	GameEngine();
	GameEngine(unsigned int, unsigned int);
	~GameEngine();

	int Init();

	void ProcessInput(float);
	void Update(float);
	void Render();


	void MainLoop();

private:
	GLFWwindow* window;
	Scene* scene;
};

#endif