
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <chrono>

#include "game.h"
//#include "resource_manager.h"
#include "scene.h"

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
	const unsigned int screenWidth = 1920;
	const unsigned int screenHeight = 1080;
	GameEngine() = default;
	GameEngine(unsigned int, unsigned int);
	~GameEngine() = default;

	int Init();

	void Update(float);
	void Render();
	void Animate(const float elapsedTime);

	void MainLoop();

private:
	GLFWwindow* window;
	Scene* scene;
};

#endif