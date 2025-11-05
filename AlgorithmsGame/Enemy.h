#ifndef ENEMY_CLASS
#define ENEMY_CLASS
#include "Attack.h"
#include "Collision.h"
#include "UpdateData.h"
#include "SpriteHandler.h"
#include "GameBase/GamesEngineeringBase.h"

class Enemy {
	float position[2];
	int health = GameParameters::Enemies::health_for_enemies[0];
	float speed = GameParameters::Enemies::speed_for_enemies[0];
	Collision collision;
	void setImagePositionAuto();
public:
	bool is_throwing_projectiles = false;  // True if enemy_type = 2 (purple plane)
	float projectile_delay = GameParameters::Projectiles::enemy_delay;
	Attack attack{ GameParameters::Enemies::attack_damage_for_enemies[0] };
	Sprite* image;
	int image_effect = 0;  // 0 for standard, 1 for damaged, 2 for dead
	Enemy();
	Enemy(Sprite*);
	Enemy(Sprite* spr, int pos[2]);
	Enemy(Sprite* spr, int pos[2], int enemy_number);
	void setStats(int health, int damage, float speed);
	void update(updateData update_data, int player_position[2]);
	void checkCollision(Collision*, float delta);
	void takeDamage(Attack*);
	int getHealth();
	float getPosition(int i);
	bool isInside(int pixel[2]);
	bool isInsideCamera(int pixel[2], int h, int w);  // 0,0 coordinates of camera
	void drawImage(GamesEngineeringBase::Window* canvas, int camera_pixel[2], int h, int w);
	void getPixelColour(int pixel[2], unsigned char colour[4]);
};

#endif
