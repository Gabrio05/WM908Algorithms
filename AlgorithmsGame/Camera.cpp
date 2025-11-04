#include "Camera.h"

// Not frame rate independent sadly
//float smoothInterpolation(float a, float b, float t) {
//	t = 3 * t * t - 2 * t * t * t;
//	return (1 - t) * a + t * b;
//}

Camera::Camera() {
	position[0] = 0.0f;
	position[1] = 0.0f;
}
Camera::Camera(int current[2]) {
	position[0] = (float)current[0];
	position[1] = (float)current[1];
}
// Update camera position smoothly based on target destination
void Camera::updatePosition(int destination[2], float delta) {
	float t = delta / time_to_destination;
	if (t > 1.0f) { t = 1.0f; }

	for (int i = 0; i < 2; i++) {
		//position[i] = smoothInterpolation(position[i], (float)destination[i], t);
		position[i] = (1 - t) * position[i] + t * (float)destination[i];  // Linear instead (still not fps independent...)
		if ((int)(position[i] + 0.5f) == destination[i]) { position[i] = (float)destination[i]; }
	}
}
int Camera::getPosition(int i) { return (int)(position[i] + 0.5f); }  // Round to nearest pixel