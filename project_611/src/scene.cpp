#include "../header/scene.h"
#include "../header/sprite.h"

void Scene::LoadScene() {
	Player* player = createPlayerGameObject(glm::vec2(300,300));
}

GameObject* Scene::GetRoot()
{
	return root;
}

Camera* Scene::GetCamera()
{
	return camera;
}

GameObject* Scene::getGameObject(const std::string& name)
{
	return gameObjects.find(name) == gameObjects.end() ? nullptr : gameObjects.find(name)->second;
}

GameObject* Scene::createGameObject(const std::string& name)
{
	GameObject* gameObject = getGameObject(name);

	if (gameObject == nullptr)
	{
		gameObject = new GameObject(name);
		gameObjects.insert(std::pair<std::string, GameObject*>(name, gameObject));
	}

	return gameObject;
}

Player* Scene::createPlayerGameObject(glm::vec2 playerPos)
{
	GameObject* playerObject = getGameObject("player");

	if (playerObject != nullptr) {
		return static_cast<Player*>(playerObject);
	}

	Player* player = new Player("player", 4.0f);
	gameObjects.insert(std::pair<std::string, GameObject*>("player", static_cast<GameObject*>(player)));

	RenderData playerSprite = { playerPos, glm::vec2(50, 50), glm::vec2(0, 0), glm::vec2(32, 32), 1.0 };
	player->CreateRenderData(std::move(playerSprite));

	return player;
}

std::map<std::string, GameObject*>& Scene::getAllGameObjects()
{
	return gameObjects;
}


