#include "Collision.h"

float pythagoras(float x, float y) {
	return (float)sqrt(x * x + y * y);
}

Collision::Collision() {}

Collision::Collision(float rad) {
	radius = rad;
}

Collision::Collision(const float rectangle[2][2]) {
	is_rectangle = true;
	rectangle_mesh[0][0] = rectangle[0][0];
	rectangle_mesh[0][1] = rectangle[0][1];
	rectangle_mesh[1][0] = rectangle[1][0];
	rectangle_mesh[1][1] = rectangle[1][1];
	float x_max;
	float y_max;
	if (-rectangle_mesh[0][0] >= rectangle_mesh[1][0]) {
		x_max = -rectangle_mesh[0][0];
	}
	else {
		x_max = rectangle_mesh[1][0];
	}
	if (-rectangle_mesh[0][1] >= rectangle_mesh[1][1]) {
		y_max = -rectangle_mesh[0][1];
	}
	else {
		y_max = rectangle_mesh[1][1];
	}
	radius = pythagoras(x_max, y_max);
}

void Collision::checkCollision(Collision* other, float delta) {
	other->clear();
	float speed = pythagoras(current_velocity[0], current_velocity[1]);
	float speed_other = pythagoras(other->current_velocity[0], other->current_velocity[1]);
	float distance = pythagoras(current_position[0] - other->current_position[0], current_position[1] - other->current_position[1]);
	float radii = radius + other->radius;
	if (distance - speed * delta - speed_other * delta > radii) {
		return;  // No collision possible
	}
	// TODO Movement based collision detection and a bunch of other stuff, the below currently is a HACK
	float new_position[2];
	float other_new_position[2];
	for (int i = 0; i < 2; i++) {
		new_position[i] = current_position[i] + current_velocity[i] * delta;
		other_new_position[i] = other->current_position[i] + other->current_velocity[i] * delta;
	}
	float new_distance = pythagoras(new_position[0] - other_new_position[0], new_position[1] - other_new_position[1]);
	if (distance <= radii) {
		has_collision_occured = true;
		other->has_collision_occured = true;
		if (is_solid || other->is_solid) { 
			has_solid_collision_occured = true;
			other->has_solid_collision_occured = true;
		}
	}
}

void Collision::clear() {
	has_collision_occured = false;
	has_solid_collision_occured = false;
}