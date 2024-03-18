#ifndef SPRITE_INDEX_H
#define SPRITE_INDEX_H

// TODO
// define sprites with significant ID's with their offset in the sprite sheet
#include "glm.hpp"

#define PLAYER_WALKING_NUM_SPRITES 7
#define PLAYER_JUMPING_NUM_SPRITES 4
#define PLAYER_IDLE_NUM_SPRITES 1
#define MONSTER_WALKING_NUM_SPRITES 1
#define TILE_NUM_SPRITES 1

enum class SpriteType {
	PlayerIdle,
	PlayerJumping,
	PlayerWalking,
	MonsterWalking,
	FloorTiles
};

class SpriteIndex : public Singleton<SpriteIndex> {
	friend class Singleton<SpriteIndex>;
public:

	glm::vec2 getSpriteOffset(SpriteType type,int index) {
		switch (type) {
		case SpriteType::PlayerIdle: {
			return playerIdle[index];
			}
		case SpriteType::PlayerJumping: {
			return playerJumping[index];
			}
		case SpriteType::PlayerWalking: {
			return playerWalking[index];
			}
		case SpriteType::MonsterWalking: {
			return tiles[index];
			}
		case SpriteType::FloorTiles: {
			return tiles[index];
			}
		}
	}
private:
	glm::vec2 playerWalking[PLAYER_WALKING_NUM_SPRITES] { glm::vec2{32,0},  glm::vec2{64,0}, glm::vec2{96, 0}, glm::vec2{128, 0}, glm::vec2{160, 0}, glm::vec2{192, 0}, glm::vec2{224,0}};
	glm::vec2 playerIdle[PLAYER_IDLE_NUM_SPRITES]{ glm::vec2{0,0}};
	glm::vec2 playerJumping[PLAYER_JUMPING_NUM_SPRITES]{ glm::vec2{256,0}, glm::vec2{288, 0}, glm::vec2{320, 0}, glm::vec2{352, 0} };
	glm::vec2 tiles[TILE_NUM_SPRITES]{ glm::vec2{0, 48} };
	glm::vec2 monsterWalking[MONSTER_WALKING_NUM_SPRITES]{ glm::vec2{0,96} };

};

#endif
