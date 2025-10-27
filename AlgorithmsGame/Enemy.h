#ifndef ENEMY_CLASS
#define ENEMY_CLASS
#include "Attack.h"
#include "Collision.h"
#include "UpdateData.h"
#include "SpriteHandler.h"
#include "GameBase/GamesEngineeringBase.h"

class Enemy {
	float position[2];
	int health;
	float speed = GameParameters::EnemyPlane::speed;
	Attack attack;
	Collision collision;
	Sprite* image;
public:
	Enemy();
	Enemy(Sprite*);
	Enemy(Sprite* spr, int pos[2]);
	void update(updateData update_data, int player_position[2]);
	void checkCollision(Collision*);
	bool isInside(int pixel[2]);
	void getPixelColour(int pixel[2], unsigned char colour[4]);
	void loadSprite();
};

#endif
