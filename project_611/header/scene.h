#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>
#include <algorithm>
#include <vector>

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
	void OuterScreenBoundingBoxes();
	void LoadPlatforms();

	/// <summary>
	/// Creates one platform
	/// </summary>
	/// <param name="uniqueName">The name of the sprites in this platform. This name must be unique in this scene</param>
	/// <param name="length">The length of the platform, in number of squares (50px X 50px)</param>
	/// <param name="position">The position of the bottom left of this platform</param>
	void CreatePlatform(std::string uniqueName, int length, glm::vec2 position);

	/// <summary>
	/// Creates one wall
	/// </summary>
	/// <param name="uniqueName">The name of the sprites in this wall. This name must be unique in this scene</param>
	/// <param name="length">The height of the wall, in number of squares (50px X 50px)</param>
	/// <param name="position">The position of the bottom left of this wall</param>
	void CreateWall(std::string uniqueName, int height, glm::vec2 position);

	// la racine de la scene
	GameObject* root;

	// tous les autres gameObjects
	std::map<std::string, GameObject*> gameObjects;
	std::map<std::string, EnvironmentObject*> environmentObjects;

	// this might be a bad idea but the ownership of these pointers is in the maps above
	std::vector<EnvironmentObject*> collidableImmovableObjects;
	std::vector<GameObject*> collidableMovableObjects;

	Collider collider;
	Camera* camera;

	int width, height;
};

#endif // SCENE_H