#include "../header/scene.h"
#include "../header/sprite.h"
#include "../header/sprite_index.h"

void Scene::LoadScene() {
	Player* player = createPlayerGameObject(glm::vec2(500, 150));
	//std::cout << "PLAYER POS: " << player->getPosition().x << " " << player->getPosition().y << std::endl;
	//std::cout << "PLAYER POS: " << player->getPosition().x + player->getHitboxOffset().x << " " << player->getPosition().y + player->getHitboxOffset().y << std::endl;
	GameObject* map[200];
	
	 //TODO : either do maps programatically like we see below, or load a prebuilt map from some file

	//this makes the floor
	for (int i=0; i < 50; ++i) {
		map[i] = createEnvironmentObject(std::to_string(i));
		RenderData tileSprite{ glm::vec2{50 * i, 0}, glm::vec2{50, 50},SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0) , glm::vec2{32, 32}, 0.5, 0.0};
		map[i]->CreateRenderData(std::move(tileSprite));
		map[i]->setHitboxDim(glm::vec2(50, 50));
	}
	//this makes the wall
	for (int j = 4; j > 0; --j) {
		map[j] = createEnvironmentObject(std::to_string(j+1*100));
		RenderData tileSprite{ glm::vec2{250, 50 * j }, glm::vec2{50, 50},SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0) , glm::vec2{32, 32}, 0.5 , 0.0};
		map[j]->CreateRenderData(std::move(tileSprite));
		map[j]->setHitboxDim(glm::vec2(50, 50));
	}
	//this makes the roof
	for (int k = 0; k < 60; ++k) {
		map[k] = createEnvironmentObject(std::to_string(k+1*1000));
		RenderData tileSprite{ glm::vec2{50 * k, 400}, glm::vec2{50, 50},SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0) , glm::vec2{32, 32}, 0.5 , 0.0};
		map[k]->CreateRenderData(std::move(tileSprite));
		map[k]->setHitboxDim(glm::vec2(50, 50));
	}

	//this is a random block
	map[2] = createEnvironmentObject("3000");
	RenderData tileSprite{ glm::vec2{600,150}, glm::vec2{50, 50},SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0) , glm::vec2{32, 32}, 0.5 , 0.0 };
	map[2]->CreateRenderData(std::move(tileSprite));
	map[2]->setHitboxDim(glm::vec2(50, 50));

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
	glm::vec2 hitboxDim = glm::vec2(33, 47);
	glm::vec2 hitboxOffset = glm::vec2(14, 0);
	

	if (playerObject != nullptr) {
		return static_cast<Player*>(playerObject);
	}

	Player* player = new Player("player", 4.0f);
	gameObjects.insert(std::pair<std::string, GameObject*>("player", static_cast<GameObject*>(player)));

	RenderData playerSprite = { playerPos, glm::vec2(64, 64), glm::vec2(0, 0), glm::vec2(32, 32), 1.0 , 0.0};
	player->CreateRenderData(std::move(playerSprite));
	player->setHitboxDim(std::move(hitboxDim));
	player->setHitboxOffset(std::move(hitboxOffset));

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
