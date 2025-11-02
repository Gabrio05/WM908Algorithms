#ifndef ENEMY_CLASS
#define ENEMY_CLASS
#include "Attack.h"
#include "Collision.h"
#include "UpdateData.h"
#include "SpriteHandler.h"
#include "GameBase/GamesEngineeringBase.h"

class Enemy {
	float position[2];
	int health = 100;
	float speed = GameParameters::EnemyPlane::speed;
	Attack attack;
	Collision collision;
	void setImagePositionAuto();
public:
	Sprite* image;
	int image_effect = 0;  // 0 for standard, 1 for damaged, 2 for dead
	Enemy();
	Enemy(Sprite*);
	Enemy(Sprite* spr, int pos[2]);
	void update(updateData update_data, int player_position[2]);
	void checkCollision(Collision*, float delta);
	void takeDamage(Attack*);
	int getHealth();
	float getPosition(int i);
	bool isInside(int pixel[2]);
	bool isInsideCamera(int pixel[2], int h, int w);  // 0,0 coordinates of camera
	void drawImage(GamesEngineeringBase::Window* canvas, int camera_pixel[2], int h, int w);
	void getPixelColour(int pixel[2], unsigned char colour[4]);
	void loadSprite();
};

#endif
