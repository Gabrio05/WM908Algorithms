#ifndef PLAYER_CLASS
#define PLAYER_CLASS
#include "SpriteHandler.h"
#include "GameParameters.h"
#include "UpdateData.h"

class Player {
	float coordinates[2];
	float speed = GameParameters::Player::speed;
	void movePlayer(updateData);
public:
	Sprite image;

	Player();
	Player(int[2]);
	void getCoordinates(int destination[2]);
	void update(updateData update_data);
};

#endif
