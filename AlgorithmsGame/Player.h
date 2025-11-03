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
	int health = GameParameters::Player::health;
	int shield = 0;
	float invulnerability_timer = GameParameters::Player::invulnerability_on_hit_per_hp;
	float speed = GameParameters::Player::speed;
	Attack attack1{ GameParameters::Player::attack1_strength };
	float attack1_cooldown = GameParameters::Player::attack1_cooldown;
	Scene* scene;
	Collision collision{ GameParameters::Player::environment_collision };
	void movePlayer(updateData);
	void performAttack1();
	void checkEnemyAttacks(float delta);  // Checks all necessary attacks, including collision and projectiles
	void checkGameOver();
public:
	Sprite image{};

	Player();
	Player(Scene* sc);
	Player(Scene* sc, int pos[2]);
	void getCoordinates(int destination[2]);
	void update(updateData update_data);
	void takeDamage(Attack* incoming_attack);
};

#endif
