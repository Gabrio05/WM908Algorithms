#include "Player.h"
#include "SceneManagement.h"

Player::Player() {
	coordinates[0] = 0.0f;
	coordinates[1] = 0.0f;
	scene = nullptr;
}

Player::Player(Scene* sc) {
	coordinates[0] = 0.0f;
	coordinates[1] = 0.0f;
	scene = sc;
}

Player::Player(Scene* sc, int set[2]) {
	coordinates[0] = (float)set[0];
	coordinates[1] = (float)set[1];
	scene = sc;
}

// Returns the base directional speed to be multiplied by x_percent and y_percent for fair movement
float fairMovement(float x_percent, float y_percent, float speed);

void Player::movePlayer(updateData update_data) {
	int directions = 0;
	float delta = update_data.delta;
	if (update_data.is_key_pressed[0x25]) {
		directions++;
	}
	if (update_data.is_key_pressed[0x26]) {
		directions++;
	}
	if (update_data.is_key_pressed[0x27]) {
		directions++;
	}
	if (update_data.is_key_pressed[0x28]) {
		directions++;
	}
	float fair_speed = 0;
	if (directions == 1) {
		fair_speed = speed;
	}
	else if (directions >= 2) {
		fair_speed = fairMovement(0.5, 0.5, speed) * 0.5;
	}
	if (update_data.is_key_pressed[0x25]) {
		coordinates[0] -= fair_speed * delta;
	}
	if (update_data.is_key_pressed[0x26]) {
		coordinates[1] -= fair_speed * delta;
	}
	if (update_data.is_key_pressed[0x27]) {
		coordinates[0] += fair_speed * delta;
	}
	if (update_data.is_key_pressed[0x28]) {
		coordinates[1] += fair_speed * delta;
	}
}

void Player::getCoordinates(int destination[2]) {
	for (int i = 0; i < 2; i++) {
		destination[i] = (int)(coordinates[i] + 0.5f);
	}
}

void Player::update(updateData update_data) {
	movePlayer(update_data);
	image.setPosition((int)(coordinates[0] + 0.5f), (int)(coordinates[1] + 0.5f));
	attack1_cooldown -= update_data.delta;
	if (attack1_cooldown <= 0) {
		performAttack1();
		attack1_cooldown += GameParameters::Player::attack1_cooldown;
	}
}

void Player::performAttack1() {
	int enemy_count = scene->getEnemyNumber();
	if (enemy_count == 0) {
		return;
	}
	float closest_enemy_squared = INFINITY;
	int closest_enemy_index = -1;
	for (int i = 0; i < enemy_count; i++) {
		float x = scene->enemies[i].getPosition(0) - coordinates[0];
		float y = scene->enemies[i].getPosition(1) - coordinates[1];
		float distance_squared = x * x + y * y;
		if (closest_enemy_squared > distance_squared) {
			closest_enemy_squared = distance_squared;
			closest_enemy_index = i;
		}
	}
	if (closest_enemy_index == -1) {
		throw EXCEPTION_ARRAY_BOUNDS_EXCEEDED;
	}
	scene->enemies[closest_enemy_index].takeDamage(&attack1);
}