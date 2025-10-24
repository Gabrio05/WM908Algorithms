#include "SceneManagement.h"

Scene::Scene() {
	camera = Camera();
	player = Player();
	background = Background();
}
void Scene::getPixelColour(int pixel[2], unsigned char colour[3]) {
	// Background -> Player -> Enemies -> Player Projectiles -> Enemy Projectiles -> Effects (if any)
	// Fake Background
	// For now, just a dot every 32 pixels
	int actual_pixel[2];
	actual_pixel[0] = camera.getPosition(0) - width / 2 + pixel[0];
	actual_pixel[1] = camera.getPosition(1) - height / 2 + pixel[1];
	if (actual_pixel[0] % 32 == 0 && actual_pixel[1] % 32 == 0) {
		colour[0] = colour[1] = colour[2] = 255;
	}
	else {
		colour[0] = colour[1] = colour[2] = 0;
	}
	// Background
	unsigned char temp_colour[4];
	background.getPixelColour(actual_pixel, temp_colour);
	if (temp_colour[3] > 0) {
		colour[0] = temp_colour[0] * temp_colour[3] / 256;
		colour[1] = temp_colour[1] * temp_colour[3] / 256;
		colour[2] = temp_colour[2] * temp_colour[3] / 256;
	}
	// Player
	if (player.image.isInside(actual_pixel[0], actual_pixel[1])) {
		unsigned char temp_colour[4];
		player.image.getPixelColour(actual_pixel, temp_colour);
		if (temp_colour[3] > 0) {
			colour[0] = temp_colour[0] * temp_colour[3] / 256;
			colour[1] = temp_colour[1] * temp_colour[3] / 256;
			colour[2] = temp_colour[2] * temp_colour[3] / 256;
		}
	}
}
void Scene::update(updateData update_data) {
	player.update(update_data);
	int destination[2];
	player.getCoordinates(destination);
	camera.updatePosition(destination, update_data.delta);
}

void Scene::loadSprite(int i, std::string filename) {
	if (i == 0) {  // Player Sprite
		player.image.load(filename);
	}
	if (i == 1) {
		background.loadAllTiles();
	}
}