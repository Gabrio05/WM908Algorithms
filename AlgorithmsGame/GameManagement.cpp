#include "GameManagement.h"

GameManager::GameManager(GamesEngineeringBase::Window& c, std::mt19937* engine) : scene{ engine }, timer{}, canvas{ c }, random_engine{ engine } {

}

void GameManager::runUpdateLoop() {
	float delta = timer.dt();
	updateData update_data = updateData(delta, &canvas);
	if (update_data.is_key_pressed['C']) {
		if (!pause_button_pressed) {
			if (is_paused) {
				is_paused = false;
			}
			else {
				is_paused = true;
				// TODO Saving Routine to save to file
			}
			pause_button_pressed = true;
		}
	}
	else {
		if (pause_button_pressed) {
			pause_button_pressed = false;
		}
	}
	if (is_paused) {
		canvas.checkInput();
		return;
	}
	if (frame_time <= delta) {
#ifdef _DEBUG
		std::cout << "Frames this second: " << frames_per_second << std::endl;
#endif
		total_frames += frames_per_second;
		frames_per_second = 0;
		frame_time += 1.0f;
		seconds_elapsed++;
		scene.average_fps = total_frames / seconds_elapsed;
	}
	frame_time -= delta;
	frames_per_second++;

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
	scene.loadMap(GameParameters::Background::map_filename);
}

void GameManager::startRoutine() {
	std::cout << "Captain! Enemies have been spotted! They'll start overwhelming us around 30 seconds after we start engaging." << std::endl;
	std::cout << "Use the arrow keys to move the plane away from enemy planes and use Z and X to trigger our manual attacks." << std::endl;
	std::cout << "You can also use C to call a temporary ceasefire. How would you like to deal with the enemies, captain?" << std::endl;
	std::cout << "'i' to engage in an infinite space" << std::endl;
	std::cout << "'f' to engage locally in a fixed space (your first officer warns you this is much, much harder)" << std::endl;
	// std::cout << "'s' to resume engaging from last saved battle" << std::endl;
	char choice = '0';
	while (choice != 'i' && choice != 'f' && choice != 's') {
		std::cout << "What is your choice captain? ";
		std::cin >> choice;
	}
	if (choice == 'f') {
		scene.setFixedWorld();
	}
	timer.dt();
}