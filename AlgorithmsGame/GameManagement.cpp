#include "GameManagement.h"

GameManager::GameManager(GamesEngineeringBase::Window& c, std::mt19937* engine) : scene{ engine }, timer{}, canvas{ c }, random_engine{ engine } {

}

void GameManager::runUpdateLoop() {
	float delta = timer.dt();
#ifdef _DEBUG
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
	scene.loadSprite(0, 0, GameParameters::Player::filename);
	scene.loadSprite(1, 0, "");
	scene.loadSprite(2, 0, GameParameters::Projectiles::filename1);
	scene.loadSprite(2, 1, GameParameters::Projectiles::filename2);
	scene.loadSprite(2, 2, GameParameters::Projectiles::filename3);
	scene.loadSprite(2, 3, GameParameters::Projectiles::filename4);
	scene.loadSprite(2, 4, GameParameters::Projectiles::filename5);
	scene.loadSprite(2, 5, GameParameters::Projectiles::filename1e);
	scene.loadSprite(2, 6, GameParameters::Projectiles::filename2e);
	scene.loadSprite(2, 7, GameParameters::Projectiles::filename3e);
	scene.loadSprite(3, 0, GameParameters::Enemies::filename1);
	scene.loadSprite(3, 1, GameParameters::Enemies::filename2);
	scene.loadSprite(3, 2, GameParameters::Enemies::filename3);
	scene.loadSprite(3, 3, GameParameters::Enemies::filename4);
}