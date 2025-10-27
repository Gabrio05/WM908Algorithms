#include "Enemy.h"

Enemy::Enemy() : attack{}, collision{ GameParameters::EnemyPlane::environment_collision } {
	position[0] = position[1] = 0.0f;
	health = 100;
	image = nullptr;
}

Enemy::Enemy(Sprite* spr) : attack{}, collision{ GameParameters::EnemyPlane::environment_collision } {
	position[0] = 0.0f;
	position[1] = 0.0f;
	health = 100;
	image = spr;
}

Enemy::Enemy(Sprite* spr, int pos[2]) : attack{}, collision{ GameParameters::EnemyPlane::environment_collision } {
	position[0] = (float)pos[0];
	position[1] = (float)pos[1];
	health = 100;
	image = spr;
}

// Returns the base directional speed to be multiplied by x_percent and y_percent for fair movement
float fair_movement(float x_percent, float y_percent, float speed) {
	float inter = speed * speed / (x_percent * x_percent + y_percent * y_percent);
	return (float)sqrt(inter);
}

void Enemy::update(updateData update_data, int player_pos[2]) {
	float delta = update_data.delta;
	float difference[2] = { (float)player_pos[0] - position[0], (float)player_pos[1] - position[1] };
	if (difference[0] == 0.0f && difference[1] == 0.0f) {
		return;
	}
	float percent[2];
	percent[0] = abs(difference[0]) / (abs(difference[0]) + abs(difference[1]));
	percent[1] = 1 - percent[0];
	float base_speed = fair_movement(percent[0], percent[1], speed);
	for (int i = 0; i < 2; i++) {
		float change = abs(base_speed * percent[i] * delta);
		if (abs(difference[i]) < change) {
			position[i] = (float)player_pos[i];
		} 
		else if (difference[i] < 0) {
			position[i] -= change;
		}
		else {
			position[i] += change;
		}
	}
}

bool Enemy::isInside(int pixel[2]) {
	image->setPosition((int)(position[0] + 0.5f), (int)(position[1] + 0.5f));
	return image->isInside(pixel[0], pixel[1]);
}

void Enemy::getPixelColour(int pixel[2], unsigned char colour[4]) {
	image->setPosition((int)(position[0] + 0.5f), (int)(position[1] + 0.5f));
	image->getPixelColour(pixel, colour);
}

void Enemy::loadSprite() {
	image->image.load(GameParameters::EnemyPlane::filename);
}