#ifndef PLAYER_CLASS
#define PLAYER_CLASS
class Scene;
#include "SpriteHandler.h"
#include "GameParameters.h"
#include "UpdateData.h"
#include "Collision.h"
#include "Attack.h"

class Player {
	float coordinates[2];
	float speed = GameParameters::Player::speed;
	Attack attack1{ GameParameters::Player::attack1_strength };
	float attack1_cooldown = GameParameters::Player::attack1_cooldown;
	Scene* scene;
	Collision collision{ GameParameters::Player::environment_collision };
	void movePlayer(updateData);
	void performAttack1();
public:
	Sprite image{};

	Player();
	Player(Scene* sc);
	Player(Scene* sc, int pos[2]);
	void getCoordinates(int destination[2]);
	void update(updateData update_data);
};

#endif
