#ifndef COLLISION_CLASS
#define COLLISION_CLASS
#include "GameBase/GamesEngineeringBase.h"

class Collision {
public:
	float current_position[2] { 0.0f, 0.0f };
	bool is_rectangle = false;
	float radius = 0.0f;
	float rectangle_mesh[2][2] { {0.0f, 0.0f}, {0.0f, 0.0f } };
	bool is_solid = false;  // Solid/stopping collision occurs if at least one entity has is_solid == true
	float current_velocity[2] { 0.0f, 0.0f };
	bool has_collision_occured = false;
	bool has_solid_collision_occured = false;
	float collision_time = 0.0f;
	float final_position[2] { 0.0f, 0.0f };
	Collision();  // Dot collision, cannot be used with another dot collision
	Collision(float rad);  // Circle of radius
	Collision(const float rectangle[2][2]);  // Rectangle collision
	// void setPosition(float current_position[2]);
	void checkCollision(Collision*, float);
	void clear();
};

#endif
