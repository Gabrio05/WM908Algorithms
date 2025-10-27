#include "Player.h"

Player::Player() : image{}, collision{ GameParameters::Player::environment_collision } {
	coordinates[0] = 0.0f;
	coordinates[1] = 0.0f;
	//scene = nullptr;
}

//Player::Player(Scene* sc) {
//	image = Sprite();
//	coordinates[0] = 0.0f;
//	coordinates[1] = 0.0f;
//	scene = sc;
//	//collision = Collision(GameParameters::Player::environment_collision);
//}
//
//Player::Player(Scene* sc, int set[2]) {
//	image = Sprite();
//	coordinates[0] = (float)set[0];
//	coordinates[1] = (float)set[1];
//	scene = sc;
//	//collision = Collision(GameParameters::Player::environment_collision);
//}

void Player::movePlayer(updateData update_data) {
	float delta = update_data.delta;
	if (update_data.is_key_pressed[0x25]) {
		coordinates[0] -= speed * delta;
	}
	if (update_data.is_key_pressed[0x28]) {
		coordinates[1] += speed * delta;
	}
	if (update_data.is_key_pressed[0x27]) {
		coordinates[0] += speed * delta;
	}
	if (update_data.is_key_pressed[0x26]) {
		coordinates[1] -= speed * delta;
	}
}

void Player::getCoordinates(int destination[2]) {
	for (int i = 0; i < 2; i++) {
		destination[i] = (int)(coordinates[i] + 0.5f);
	}
}

void Player::update(updateData update_data) {
	movePlayer(update_data);
	image.setPosition(coordinates[0], coordinates[1]);
}