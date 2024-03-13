#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "singleton.h"
#include <glfw3.h>


enum Key {
	W,
	A,
	S,
	D,
	NUM_KEYS // this must always be the last thing
};

class InputManager : public Singleton<InputManager> {
	friend class Singleton<InputManager>;

public:


	void ProcessInput(GLFWwindow* window);



	bool pressedKey[NUM_KEYS]{ false };

};

#endif // !INPUT_MANAGER_H
