#include "Enemy.h"

Enemy::Enemy() : collision{ GameParameters::Enemies::environment_collision[0] } {
	position[0] = position[1] = 0.0f;
	image = nullptr;
	collision.current_position[0] = position[0];
	collision.current_position[1] = position[1];
}

Enemy::Enemy(Sprite* spr) : collision{ GameParameters::Enemies::environment_collision[0] } {
	position[0] = 0.0f;
	position[1] = 0.0f;
	image = spr;
	collision.current_position[0] = position[0];
	collision.current_position[1] = position[1];
}

Enemy::Enemy(Sprite* spr, int pos[2]) : collision{ GameParameters::Enemies::environment_collision[0] } {
	position[0] = (float)pos[0];
	position[1] = (float)pos[1];
	image = spr;
	collision.current_position[0] = position[0];
	collision.current_position[1] = position[1];
}

Enemy::Enemy(Sprite* spr, int pos[2], int enemy_number) : collision{ GameParameters::Enemies::environment_collision[enemy_number] } {
	position[0] = (float)pos[0];
	position[1] = (float)pos[1];
	image = spr;
	collision.current_position[0] = position[0];
	collision.current_position[1] = position[1];
	setStats(GameParameters::Enemies::health_for_enemies[enemy_number],
			 GameParameters::Enemies::attack_damage_for_enemies[enemy_number],
			 GameParameters::Enemies::speed_for_enemies[enemy_number]);
	if (enemy_number == 2) { is_throwing_projectiles = true; }
}

void Enemy::setStats(int h, int damage, float sp) {
	health = h;
	attack = Attack{ damage };
	speed = sp;
}

void Enemy::setImagePositionAuto() {
	image->setPosition((int)(position[0] + 0.5f), (int)(position[1] + 0.5f));
}

void Enemy::checkCollision(Collision* coll, float delta) {
	return collision.checkCollision(coll, delta);
}

void Enemy::takeDamage(Attack* incoming_attack) {
	health -= incoming_attack->damage;
	if (health <= 0) {
		image_effect = 2;
	}
	else {
		image_effect = 1;
	}
}

int Enemy::getHealth() { return health; }

float Enemy::getPosition(int i) { return position[i]; }

// Returns the base directional speed to be multiplied by x_percent and y_percent for fair movement
float fairMovement(float x_percent, float y_percent, float speed);

void Enemy::update(updateData update_data, int player_pos[2]) {
	float delta = update_data.delta;
	float difference[2] = { (float)player_pos[0] - position[0], (float)player_pos[1] - position[1] };
	if (difference[0] == 0.0f && difference[1] == 0.0f 
		|| is_throwing_projectiles && abs(difference[0]) < GameParameters::Projectiles::max_enemy_distance_x 
								   && abs(difference[1]) < GameParameters::Projectiles::max_enemy_distance_y) {
		return;
	}
	float percent[2];
	percent[0] = abs(difference[0]) / (abs(difference[0]) + abs(difference[1]));
	percent[1] = 1 - percent[0];
	float base_speed = fairMovement(percent[0], percent[1], speed);
	for (int i = 0; i < 2; i++) {
		float change = abs(base_speed * percent[i] * delta);
		if (abs(difference[i]) < change) {
			position[i] = (float)player_pos[i];
		} 
		else if (difference[i] < 0) {
			position[i] -= change;
			collision.current_velocity[i] = -change / delta;
		}
		else {
			position[i] += change;
			collision.current_velocity[i] = change / delta;
		}
		collision.current_position[i] = position[i];
	}
}

bool Enemy::isInside(int pixel[2]) {
	setImagePositionAuto();
	return image->isInside(pixel[0], pixel[1]);
}

bool Enemy::isInsideCamera(int pixel[2], int h, int w) {
	if (pixel[0] - (int)image->image.width < position[0]
		&& pixel[0] + w + (int)image->image.width > position[0]
		&& pixel[1] - (int)image->image.height < position[1]
		&& pixel[1] + h + (int)image->image.height > position[1]) {
		return true;
	}
	return false;
}

void Enemy::drawImage(GamesEngineeringBase::Window* canvas, int camera_pixel[2], int h, int w) {
	if (!isInsideCamera(camera_pixel, h, w)) {
		return;
	}
	image->setPosition(image->image.width / 2, image->image.height / 2);
	for (int y = 0; y < (int)image->image.height; y++) {
		for (int x = 0; x < (int)image->image.width; x++) {
			int pixel[2];
			pixel[0] = (int)(position[0] + 0.5f) - (int)image->image.width / 2 + x;
			pixel[1] = (int)(position[1] + 0.5f) - (int)image->image.height / 2 + y;
			if (pixel[0] < camera_pixel[0] || pixel[0] >= camera_pixel[0] + w
				|| pixel[1] < camera_pixel[1] || pixel[1] >= camera_pixel[1] + h) {
				continue;
			}
			int target[2] = { x, y };
			unsigned char temp_colour[4]{};
			image->getPixelColour(target, temp_colour);
			if (temp_colour[3] > 0) {
				if (image_effect > 0) {
					if (image_effect == 1) {
						temp_colour[0] = min(255, (int)temp_colour[0] * 2);
						temp_colour[1] = min(255, (int)temp_colour[1] * 2);
						temp_colour[2] = min(255, (int)temp_colour[2] * 2);
					}
					else if (image_effect == 2) {
						temp_colour[0] = min(255, (int)temp_colour[0] * 5);
					}
				}
				canvas->draw(pixel[0] - camera_pixel[0], pixel[1] - camera_pixel[1], temp_colour);
			}
		}
	}
	image_effect = 0;
}

void Enemy::getPixelColour(int pixel[2], unsigned char colour[4]) {
	setImagePositionAuto();
	image->getPixelColour(pixel, colour);
}