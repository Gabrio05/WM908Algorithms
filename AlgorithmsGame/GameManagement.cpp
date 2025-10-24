#include "GameManagement.h"

GameManager::GameManager(GamesEngineeringBase::Window* c) {
	canvas = c;
	scene = Scene();
	scene.loadSprite(0, GameParameters::Player::filename);
	scene.loadSprite(1, "");
	timer = GamesEngineeringBase::Timer();
}

void GameManager::runUpdateLoop() {
	float delta = timer.dt();
#ifdef DEBUG
	if (frame_time <= delta) {
		std::cout << "Frames this second: " << frames_per_second << std::endl;
		frames_per_second = 0;
		frame_time += 1.0f;
	}
	frame_time -= delta;
	frames_per_second++;
#endif
	updateData update_data = updateData(delta, canvas);
	scene.update(update_data);
	canvas->clear();
	drawImage();
	canvas->present();
}

void GameManager::drawImage() {
	for (int i = 0; i < GameParameters::window_height; i++) {
		for (int j = 0; j < GameParameters::window_width; j++) {
			unsigned char colour[3];
			int pixel[2];
			pixel[0] = j;
			pixel[1] = i;
			scene.getPixelColour(pixel, colour);
			canvas->draw(j, i, colour[0], colour[1], colour[2]);
		}
	}
}