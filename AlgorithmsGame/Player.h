#ifndef PLAYER_CLASS
#define PLAYER_CLASS
#include "SpriteHandler.h"
#include "GameParameters.h"
#include "UpdateData.h"

class Player {
	float coordinates[2];
	float speed = GameParameters::Player::speed;
	void movePlayer(UpdateData);
public:
	Sprite image;

	Player();
	void getCoordinates(int destination[2]);
	void update(UpdateData update_data);
};

#endif
