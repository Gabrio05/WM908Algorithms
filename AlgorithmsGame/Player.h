#ifndef PLAYER_CLASS
#define PLAYER_CLASS
//#include "SceneManagement.h"
#include "SpriteHandler.h"
#include "GameParameters.h"
#include "UpdateData.h"
#include "Collision.h"

class Player {
	float coordinates[2];
	float speed = GameParameters::Player::speed;
	void movePlayer(updateData);
	//Scene* scene;
	Collision collision;
public:
	Sprite image;

	Player();
	//Player(Scene* sc);
	//Player(Scene* sc, int pos[2]);
	void getCoordinates(int destination[2]);
	void update(updateData update_data);
};

#endif
