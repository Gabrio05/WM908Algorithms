#ifndef CAMERA_PLAYER
#define CAMERA_PLAYER
#include "GameParameters.h"

/* Camera controls, should only be used by Scene */
class Camera {
	float position[2];  // Center of camera
	float time_to_destination = GameParameters::Camera::time_to_destination;
public:
	Camera();  // Camera at position 0,0
	Camera(int[2]);  // Length 2 array to set x and y of camera
	void updatePosition(int destination[2], float t);  // Smooth interpolation to target based on t in [0, 1]
	int getPosition(int i);  // i = 0 for x, i = 1 for y
};

#endif
