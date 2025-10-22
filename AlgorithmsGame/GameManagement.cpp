#include "GameManagement.h"

GameManager::GameManager(GamesEngineeringBase::Window* c) {
	canvas = c;
	scene = Scene();
	scene.loadSprite(0, GameParameters::Player::fileName);
	timer = GamesEngineeringBase::Timer();
}

void GameManager::runUpdateLoop() {
	canvas->clear();
	float delta = timer.dt();
	UpdateData update_data = UpdateData(delta, canvas);
	scene.update(update_data);
	drawImage();
	canvas->present();
}

void GameManager::drawImage() {
	for (int i = 0; i < GameParameters::window_height; i++) {
		for (int j = 0; j < GameParameters::window_width; j++) {
			int colour[3];
			int pixel[2];
			pixel[0] = j;
			pixel[1] = i;
			scene.getPixelColour(pixel, colour);
			canvas->draw(j, i, colour[0], colour[1], colour[2]);
		}
	}
}