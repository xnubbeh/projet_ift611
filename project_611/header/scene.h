#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>
#include <algorithm>

#include "singleton.h"
#include "game_object.h"
#include "environment_object.h"
#include "camera.h"
#include "player.h"
#include "collider.h"

class Scene : public Singleton<Scene> {
	friend class Singleton<Scene>;

public:
	Scene() = default;
	~Scene() = default;
	GameObject* GetRoot();
	Camera* GetCamera();

	GameObject* getGameObject(const std::string& name);
	GameObject* createGameObject(const std::string& name);

	EnvironmentObject* getEnvironmentObject(const std::string& name);
	EnvironmentObject* createEnvironmentObject(const std::string& name);

	std::map<std::string, GameObject*>& getAllGameObjects();
	void LoadScene();

	Player* createPlayerGameObject(glm::vec2 pos);
	GameObject* playerObject;
	RenderData playerSprite;

	void movePlayerPos(glm::vec2); 

	void Animate(const float elapsedTime);
	

private:
	// la racine de la scene
	GameObject* root;

	// tous les autres gameObjects
	std::map<std::string, GameObject*> gameObjects;
	std::map<std::string, EnvironmentObject*> environmentObjects;

	Collider collider;
	Camera* camera;

	int width, height;

};

#endif // SCENE_H