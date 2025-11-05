#include "Projectile.h"

Projectile::Projectile() : attack{ 20 } {

}

Projectile::Projectile(Sprite* spr, bool is_friendly, float pos[2], int attack_damage) : attack{ attack_damage } {
	image = spr;
	is_player_friendly = is_friendly;
	position[0] = pos[0];
	position[1] = pos[1];
}

Projectile::Projectile(Sprite* spr, bool is_friendly, float pos[2], int attack_damage, float vel[2]) : attack{ attack_damage } {
	image = spr;
	is_player_friendly = is_friendly;
	position[0] = pos[0];
	position[1] = pos[1];
	velocity_move = true;
	velocity[0] = vel[0];
	velocity[1] = vel[1];
}

void Projectile::checkCollision(Collision* coll, float delta) {
	return collision.checkCollision(coll, delta);
}

// Returns the base directional speed to be multiplied by x_percent and y_percent for fair movement
float fairMovement(float x_percent, float y_percent, float speed);

void Projectile::update(updateData update_data, int player_pos[2]) {
	float delta = update_data.delta;

	if (is_player_friendly) {
		lifespan -= delta;
		if (lifespan <= 0.0f) {
			is_used = true;
		}
	}

	if (velocity_move) {
		position[0] += velocity[0] * update_data.delta;
		position[1] += velocity[1] * update_data.delta;
		collision.current_position[0] = position[0];
		collision.current_position[1] = position[1];
		return;
	}
	float difference[2] = { (float)player_pos[0] - position[0], (float)player_pos[1] - position[1] };
	if (difference[0] == 0.0f && difference[1] == 0.0f) {
		return;
	}
	float percent[2];
	percent[0] = abs(difference[0]) / (abs(difference[0]) + abs(difference[1]));
	percent[1] = 1 - percent[0];
	float base_speed = fairMovement(percent[0], percent[1], GameParameters::Projectiles::enemy_speed);
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

bool Projectile::isInsideCamera(int pixel[2], int h, int w) {
	if (pixel[0] - (int)image->image.width < position[0]
		&& pixel[0] + w + (int)image->image.width > position[0]
		&& pixel[1] - (int)image->image.height < position[1]
		&& pixel[1] + h + (int)image->image.height > position[1]) {
		return true;
	}
	return false;
}

void Projectile::drawImage(GamesEngineeringBase::Window* canvas, int camera_pixel[2], int h, int w) {
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
			image[current_sprite].getPixelColour(target, temp_colour);
			if (temp_colour[3] > 0) {
				canvas->draw(pixel[0] - camera_pixel[0], pixel[1] - camera_pixel[1], temp_colour);
			}
		}
	}
	current_sprite += 1;
	if (is_player_friendly && current_sprite >= GameParameters::Projectiles::unique_friendly_sprites
		|| !is_player_friendly && current_sprite >= GameParameters::Projectiles::unique_enemy_sprites) {
		current_sprite = 0;
	}
}