#include "SceneManagement.h"

float smoothInterpolation(float a, float b, float t) {
	t = 3 * t * t - 2 * t * t * t;
	return (1 - t) * a + t * b;
}

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
		position[i] = smoothInterpolation(position[i], destination[i], t);
		if ((int)(position[i] + 0.5f) == destination[i]) { position[i] = (float)destination[i]; }
	}
}
int Camera::getPosition(int i) { return (int)(position[i] + 0.5f); }  // Round to nearest pixel


Scene::Scene() {
	camera = Camera();
	player = Player();
}
void Scene::getPixelColour(int pixel[2], int colour[3]) {
	// Background -> Effects (if any) -> Hero -> Enemies -> Hero Projectiles -> Enemy Projectiles
	// Background
	int actual_pixel[2];
	actual_pixel[0] = camera.getPosition(0) - width / 2 + pixel[0];
	actual_pixel[1] = camera.getPosition(1) - height / 2 + pixel[1];
	if (actual_pixel[0] % 50 == 0 && actual_pixel[1] % 50 == 0) {  // HACK
		colour[0] = colour[1] = colour[2] = 255;
	}
	else {
		colour[0] = colour[1] = colour[2] = 0;
	}
	if (player.image.isInside(actual_pixel[0], actual_pixel[1])) {
		unsigned char temp_colour[4];
		player.image.getPixelColour(actual_pixel, temp_colour);
		if (temp_colour[3] > 0) {
			colour[0] = temp_colour[0];
			colour[1] = temp_colour[1];
			colour[2] = temp_colour[2];
		}
	}
}
void Scene::update(UpdateData update_data) {
	int destination[2];
	player.getCoordinates(destination);
	camera.updatePosition(destination, update_data.delta);
	player.update(update_data);
}

void Scene::loadSprite(int i, std::string fileName) {
	if (i == 0) {
		player.image.load(fileName);
	}
}