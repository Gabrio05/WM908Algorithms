#ifndef PLAYER_CLASS
#define PLAYER_CLASS
class Scene;
#include <iostream>
#include "SpriteHandler.h"
#include "GameParameters.h"
#include "UpdateData.h"
#include "Collision.h"
#include "Attack.h"

class Player {
	float coordinates[2];
	int health = GameParameters::Player::health;
	bool is_dead = false;
	int shield = 0;
	float invulnerability_timer = 0.0f;
	float shield_timer = GameParameters::Player::invulnerability_on_hit_per_hp;
	float speed = GameParameters::Player::speed;
	Attack attack1{ GameParameters::Player::attack1_strength };
	Attack attack2{ GameParameters::Player::attack2_strength };
	Attack attack3{ GameParameters::Player::attack3_strength };
	float attack1_cooldown = GameParameters::Player::attack1_cooldown;
	float attack2_cooldown = 0.0f;
	float attack3_cooldown = 0.0f;
	float future_attack3_projectile_velocity[2]{};
	Scene* scene;
	Collision collision{ GameParameters::Player::environment_collision };
	bool fixed_world = false;
	void movePlayer(updateData);
	void performAttack1();  // Continuous
	void performAttack2();  // AoE
	void performAttack3();  // Flare projectile
	void checkEnemyAttacks(float delta);  // Checks all necessary attacks, including collision and projectiles
	void checkGameOver();
public:
	Sprite image{};

	Player();
	Player(Scene* sc);
	Player(Scene* sc, int pos[2]);
	void setFixedWorld();
	void getCoordinates(int destination[2]);
	void update(updateData update_data);
	void takeDamage(Attack* incoming_attack);
};

#endif
