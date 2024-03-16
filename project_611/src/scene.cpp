#include "../header/scene.h"
#include "../header/sprite.h"
#include "../header/sprite_index.h"

void Scene::LoadScene() {
	Player* player = createPlayerGameObject(glm::vec2(300,300));
	GameObject* map[200];
	
	 //TODO : either do maps programatically like we see below, or load a prebuilt map from some file
	int i = 0;
	for (; i < 50; ++i) {
		map[i] = createEnvironmentObject(std::to_string(i));
		RenderData tileSprite{ glm::vec2{50 * i, 0}, glm::vec2{50, 50},SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0) , glm::vec2{32, 32}, 0.5, 0.0};
		map[i]->CreateRenderData(std::move(tileSprite));
	}
	for (; i < 54; ++i) {
		map[i] = createEnvironmentObject(std::to_string(i));
		RenderData tileSprite{ glm::vec2{200, 50 * (i-49) }, glm::vec2{50, 50},SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0) , glm::vec2{32, 32}, 0.5 , 0.0};
		map[i]->CreateRenderData(std::move(tileSprite));
	}
	for (; i < 60; ++i) {
		map[i] = createEnvironmentObject(std::to_string(i));
		RenderData tileSprite{ glm::vec2{50 * (i-54), 400}, glm::vec2{50, 50},SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0) , glm::vec2{32, 32}, 0.5 , 0.0};
		map[i]->CreateRenderData(std::move(tileSprite));
	}

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

	RenderData playerSprite = { playerPos, glm::vec2(50, 50), glm::vec2(0, 0), glm::vec2(32, 32), 1.0 , 0.0};
	player->CreateRenderData(std::move(playerSprite));

	return player;
}

EnvironmentObject* Scene::getEnvironmentObject(const std::string& name) {
	return environmentObjects.find(name) == environmentObjects.end() ? nullptr : environmentObjects.find(name)->second;
}

EnvironmentObject* Scene::createEnvironmentObject(const std::string& name) {
	EnvironmentObject* environmentObject = getEnvironmentObject(name);

	if (environmentObject == nullptr)
	{
		environmentObject = new EnvironmentObject(name);
		environmentObjects.insert(std::pair<std::string, EnvironmentObject*>(name, environmentObject));
	}

	return environmentObject;
}

std::map<std::string, GameObject*>& Scene::getAllGameObjects()
{
	return gameObjects;
}

void Scene::Animate(const float elapsedTime) {
	
	std::for_each(this->getAllGameObjects().begin(), this->getAllGameObjects().end(), [elapsedTime](const std::pair<std::string, GameObject*>& pair) {
		pair.second->Animate(elapsedTime);
		});
	collider.checkCollision(gameObjects, environmentObjects);
}
