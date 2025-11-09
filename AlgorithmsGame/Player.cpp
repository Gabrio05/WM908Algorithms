#include "Player.h"
#include "SceneManagement.h"
#ifdef _DEBUG
#include <print>
#endif

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

void Player::saveToSave(std::ofstream* file) {
	*file << coordinates[0] << ',';
	*file << coordinates[1] << ',';
	*file << health << ',';
	*file << shield << ',';
	*file << invulnerability_timer << ',';
	*file << shield_timer << ',';
	*file << attack1_cooldown << ',';
	*file << attack2_cooldown << ',';
	*file << attack3_cooldown << ',';
	*file << future_attack3_projectile_velocity[0] << ',';
	*file << future_attack3_projectile_velocity[1] << ',';
	*file << '\n';
}

void Player::loadFromSave(float coord[2], int h, int sh, float inv, float shield_t, float at1, float at2, float at3, float at3_vel[2]) {
	coordinates[0] = coord[0];
	coordinates[1] = coord[1];
	health = h;
	shield = sh;
	invulnerability_timer = inv;
	shield_timer = shield_t;
	attack1_cooldown = at1;
	attack2_cooldown = at2;
	attack3_cooldown = at3;
	future_attack3_projectile_velocity[0] = at3_vel[0];
	future_attack3_projectile_velocity[1] = at3_vel[1];
}

void Player::setFixedWorld() {
	fixed_world = true;
	coordinates[0] = GameParameters::Background::fixed_world_spawn_point[0];
	coordinates[1] = GameParameters::Background::fixed_world_spawn_point[1];
}

void Player::takeDamage(Attack* incoming_attack) {
	if (invulnerability_timer > 0.0f) { return; }
	invulnerability_timer = GameParameters::Player::global_invulnerability;
	int attack_damage = incoming_attack->damage;
#ifdef _DEBUG
	std::print("dam: {0}, timer: {1}, shield: {2}, shield_timer: {3}\n", attack_damage, invulnerability_timer, shield, shield_timer);
#endif
	if (shield > 0) {
		if (shield >= attack_damage) {
			shield -= attack_damage;
			image.image_effect = 3;
			return;
		}
		attack_damage -= shield;
		shield = 0;
	}
	health -= attack_damage;
	shield += attack_damage * GameParameters::Player::shield_multiplier;
	shield_timer = GameParameters::Player::invulnerability_on_hit_per_hp;
	image.image_effect = 1;
	if (health <= 0) {
		image.image_effect = 2;
	}
}

// Returns the base directional speed to be multiplied by x_percent and y_percent for fair movement
float fairMovement(float x_percent, float y_percent, float speed);

void Player::movePlayer(updateData update_data) {
	collision.current_velocity[0] = 0.0f;
	collision.current_velocity[1] = 0.0f;
	int directions = 0;
	float delta = update_data.delta;
	// Count directions to get fair speed (diagonal or ortogonal)
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
		future_attack3_projectile_velocity[0] = 0.0f;
		future_attack3_projectile_velocity[1] = 0.0f;
	}
	else if (directions >= 2) {
		fair_speed = (float)(fairMovement(0.5, 0.5, speed) * 0.5);
		future_attack3_projectile_velocity[0] = 0.0f;
		future_attack3_projectile_velocity[1] = 0.0f;
	}
	// Process Movements
	if (update_data.is_key_pressed[0x25]) {
		coordinates[0] -= fair_speed * delta;
		collision.current_velocity[0] = -fair_speed;
		future_attack3_projectile_velocity[0] += -fair_speed * GameParameters::Projectiles::friendly_speed / speed;
	}
	if (update_data.is_key_pressed[0x26]) {
		coordinates[1] -= fair_speed * delta;
		collision.current_velocity[1] = -fair_speed;
		future_attack3_projectile_velocity[1] += -fair_speed * GameParameters::Projectiles::friendly_speed / speed;
	}
	if (update_data.is_key_pressed[0x27]) {
		coordinates[0] += fair_speed * delta;
		collision.current_velocity[0] = fair_speed;
		future_attack3_projectile_velocity[0] += fair_speed * GameParameters::Projectiles::friendly_speed / speed;
	}
	if (update_data.is_key_pressed[0x28]) {
		coordinates[1] += fair_speed * delta;
		collision.current_velocity[1] = fair_speed;
		future_attack3_projectile_velocity[1] += fair_speed * GameParameters::Projectiles::friendly_speed / speed;
	}
	// If fixed world, bound player
	if (fixed_world) {
		for (int i = 0; i < 2; i++) {
			if (coordinates[i] < GameParameters::Background::fixed_world_player_constraints[0][i]) {
				coordinates[i] = GameParameters::Background::fixed_world_player_constraints[0][i];
			}
			else if (coordinates[i] > GameParameters::Background::fixed_world_player_constraints[1][i]) {
				coordinates[i] = GameParameters::Background::fixed_world_player_constraints[1][i];
			}
		}
	}
	// Update collision
	collision.current_position[0] = coordinates[0];
	collision.current_position[1] = coordinates[1];
}

void Player::getCoordinates(int destination[2]) {
	for (int i = 0; i < 2; i++) {
		destination[i] = (int)(coordinates[i] + 0.5f);
	}
}

void Player::update(updateData update_data) {
	image.image_effect = 0;  // Clear any sprite effects on player
	movePlayer(update_data);
	image.setPosition((int)(coordinates[0] + 0.5f), (int)(coordinates[1] + 0.5f));
	attack1_cooldown -= update_data.delta;
	attack2_cooldown -= update_data.delta;
	attack3_cooldown -= update_data.delta;
	if (attack1_cooldown <= 0) {
		performAttack1();
		attack1_cooldown += GameParameters::Player::attack1_cooldown;
	}
	attack2_cooldown -= update_data.delta;
	if (attack2_cooldown <= 0 && update_data.is_key_pressed['Z']) {
		performAttack2();
		attack2_cooldown = GameParameters::Player::attack2_cooldown;
	}
	if (attack3_cooldown <= 0 && update_data.is_key_pressed['X']) {
		performAttack3();
		attack3_cooldown = GameParameters::Player::attack3_cooldown;
	}
	if (invulnerability_timer > 0.0f) {
		invulnerability_timer -= update_data.delta;
	}
	if (shield > 0) {
		shield_timer -= update_data.delta;
		if (shield_timer <= 0) {
			shield--;
			shield_timer += GameParameters::Player::invulnerability_on_hit_per_hp;
		}
	}
	checkEnemyAttacks(update_data.delta);
	checkGameOver();
}

void Player::checkEnemyAttacks(float delta) {
	// Enemies
	int enemy_count = scene->getEnemyNumber();
	for (int i = 0; i < enemy_count; i++) {
		scene->checkCollision(&collision, i, delta);
		if (collision.has_collision_occured) {
			takeDamage(&scene->enemies[i].attack);
		}
	}
	// Projectiles
	int projectile_count = scene->getProjectileNumber();
	for (int i = 0; i < projectile_count; i++) {
		if (!scene->projectiles[i].friendliness()) {
			scene->checkProjectileCollision(&collision, i, delta);
			if (collision.has_collision_occured) {
				takeDamage(&scene->enemies[i].attack);
				scene->projectiles[i].is_used = true;
			}
		}
	}
}

void Player::performAttack1() {
	int enemy_count = scene->getEnemyNumber();
	if (enemy_count <= 0) {
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
#ifdef _DEBUG
	if (closest_enemy_index == -1) {
		throw EXCEPTION_ARRAY_BOUNDS_EXCEEDED;
	}
#endif
	scene->enemies[closest_enemy_index].takeDamage(&attack1);
}

float pythagoras(float x, float y);

void Player::performAttack2() {
	int enemy_count = scene->getEnemyNumber();
	if (enemy_count <= 0) {
		return;
	}
	if (enemy_count <= GameParameters::Player::attack2_enemies_to_attack) {
		for (int i = 0; i < enemy_count; i++) {
			scene->enemies[i].takeDamage(&attack2);
		}
		return;
	}
	int indices[GameParameters::Player::attack2_enemies_to_attack];
	// If equal health, check distance (useful given most enemies are the same health at spawn)
	float distance_to_player[GameParameters::Enemies::max_enemy_count];
	int nth_highest_index = 0;  // Enemy index that is currently scheduled to be attacked but has the lowest health (and highest distance otherwise)
	for (int i = 0; i < enemy_count; i++) {
		distance_to_player[i] = pythagoras(coordinates[0] - scene->enemies[i].getPosition(0), coordinates[1] - scene->enemies[i].getPosition(1));
	}
	// Start-up
	for (int i = 0; i < GameParameters::Player::attack2_enemies_to_attack; i++) {
		int enemy_health = scene->enemies[i].getHealth();
		indices[i] = i;
		if (enemy_health < scene->enemies[nth_highest_index].getHealth()
			|| enemy_health == scene->enemies[nth_highest_index].getHealth() 
			&& distance_to_player[i] > distance_to_player[nth_highest_index]) {
			nth_highest_index = i;
		}
	}
	// Loop
	for (int i = GameParameters::Player::attack2_enemies_to_attack; i < enemy_count; i++) {
		int enemy_health = scene->enemies[i].getHealth();
		if (enemy_health > scene->enemies[nth_highest_index].getHealth()
			|| enemy_health == scene->enemies[nth_highest_index].getHealth() 
			&& distance_to_player[i] < distance_to_player[nth_highest_index]) {
			int previous_nth = nth_highest_index;
			nth_highest_index = i;
			for (int j = 0; j < GameParameters::Player::attack2_enemies_to_attack; j++) {
				if (indices[j] == previous_nth) {
					indices[j] = i;
				}
				int other_enemy_health = scene->enemies[indices[j]].getHealth();
				if (other_enemy_health < scene->enemies[nth_highest_index].getHealth() 
					|| other_enemy_health == scene->enemies[nth_highest_index].getHealth()
				    && distance_to_player[indices[j]] > distance_to_player[nth_highest_index]) {
					nth_highest_index = indices[j];
				}
			}
		}
	}
#ifdef _DEBUG
	for (int i = 0; i < GameParameters::Player::attack2_enemies_to_attack; i++) {
		std::print("Targetted plane {0} with {1} health and {2} distance.\n", indices[i], scene->enemies[indices[i]].getHealth(), distance_to_player[indices[i]]);
	}
#endif
	// Finally, damage
	for (int i = -1; i < GameParameters::Player::attack2_enemies_to_attack; i++) {
		float base_pos[2];
		if (i == -1) {
			base_pos[0] = coordinates[0];
			base_pos[1] = coordinates[1];
		}
		else {
			base_pos[0] = scene->enemies[indices[i]].getPosition(0);
			base_pos[1] = scene->enemies[indices[i]].getPosition(1);
		}
		for (int j = 0; j < enemy_count; j++) {
			int dist = pythagoras(base_pos[0] - scene->enemies[j].getPosition(0), base_pos[1] - scene->enemies[j].getPosition(1));
			if (dist <= GameParameters::Player::attack2_aoe_radius) {
				scene->enemies[j].takeDamage(&attack2);
			}
		}
	}
}

void Player::performAttack3() {
	scene->throwProjectile(true, coordinates, attack3.damage, future_attack3_projectile_velocity);
}

void Player::checkGameOver() {
	if (health <= 0) {
		coordinates[0] += 100000;
		if (!is_dead) {
			std::cout << "Captain? Captain?! CAPTAIN!!!" << std::endl;
			std::cout << "(You survived for " << scene->getTotalTimeElapsed() << " seconds and killed " << scene->getTotalKills() << " enemies.)" << std::endl;
			std::cout << "(The game ran at an average of " << scene->average_fps << " fps.)" << std::endl;
			is_dead = true;
		}
	}
}