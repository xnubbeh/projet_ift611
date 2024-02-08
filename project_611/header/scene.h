#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>

#include "singleton.h"
#include "game_object.h"
#include "camera.h"

class Scene : public Singleton<Scene> {
	friend class Singleton<Scene>;

public:
	Scene() = default;
	~Scene() = default;
	GameObject* GetRoot();
	Camera* GetCamera();
	GameObject* getGameObject(const std::string& name);
	GameObject* createGameObject(const std::string& name);
	std::map<std::string, GameObject*>& getAllGameObjects();




private:
	// la racine de la scene
	GameObject* root;
	// tous les autres gameObjects
	std::map<std::string, GameObject*> gameObjects;

	Camera* camera;

	int width, height;

};

#endif // SCENE_H