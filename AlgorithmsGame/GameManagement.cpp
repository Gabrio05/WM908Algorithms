#include "GameManagement.h"

GameManager::GameManager(GamesEngineeringBase::Window& c, std::mt19937* engine) : scene{ engine }, timer{}, canvas{ c }, random_engine{ engine } {

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
	updateData update_data = updateData(delta, &canvas);
	scene.update(update_data);
	canvas.clear();
	scene.drawImage(&canvas);
	canvas.present();
}

void GameManager::loadAll() {
	scene.loadSprite(0, GameParameters::Player::filename);
	scene.loadSprite(1, "");
	scene.loadSprite(2, "");
}