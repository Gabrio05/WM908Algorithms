#ifndef PROJECTILE
#define PROJECTILE
#include "Attack.h"
#include "SpriteHandler.h"
#include "UpdateData.h"
#include "Collision.h"

class Projectile {
	float position[2]{};
	bool velocity_move = false;  // Move in a straight line according to velocity
	float velocity[2]{};
	float lifespan = GameParameters::Projectiles::friendly_lifespan;
	Collision collision{ GameParameters::Projectiles::radius };
	bool is_player_friendly = true;
public:
	Attack attack;
	Sprite* image;
	int current_sprite = 0;
	bool is_used = false;

	Projectile();
	Projectile(Sprite* spr, bool is_friendly, float pos[2], int attack_damage);
	Projectile(Sprite* spr, bool is_friendly, float pos[2], int attack_damage, float vel[2]);
	const bool friendliness() { return is_player_friendly; }
	Collision* getCollisionPointer() { return &collision; }
	int getPosition(int i) { return (int)(position[i] + 0.5f); }
	void checkCollision(Collision* coll, float delta);
	void update(updateData update_data, int player_pos[2]);
	bool isInsideCamera(int pixel[2], int h, int w);
	void drawImage(GamesEngineeringBase::Window* canvas, int camera_pixel[2], int h, int w);
};

#endif
