#include "SceneManagement.h"
#ifdef _DEBUG
#include <print>
#endif

Scene::Scene() : player{this} {
	enemy_sprites = new Sprite[GameParameters::Enemies::unique_enemies]{};
	enemies = new Enemy[GameParameters::Enemies::max_enemy_count]{};
	spawnEnemy();
	random_engine = nullptr;
}

Scene::Scene(std::mt19937* engine) : player{ this }, random_engine{ engine } {
	enemy_sprites = new Sprite[GameParameters::Enemies::unique_enemies]{};
	enemies = new Enemy[GameParameters::Enemies::max_enemy_count]{};
	spawnEnemy();
}

Scene::~Scene() {
	delete[] enemy_sprites;
	delete[] enemies;
}

int Scene::getEnemyNumber() { return enemy_count; }

void Scene::checkCollision(Collision* collision, int enemy_number, float delta) {
	return enemies[enemy_number].checkCollision(collision, delta);
}

void Scene::drawImage_PerPixel(GamesEngineeringBase::Window* canvas, int index_function, int world_pixel[2]) {
	for (int y = 0; y < (int)canvas->getHeight(); y++) {
		for (int x = 0; x < (int)canvas->getWidth(); x++) {
			int actual_pixel[2];
			actual_pixel[0] = world_pixel[0] + x;
			actual_pixel[1] = world_pixel[1] + y;
			switch (index_function) {
			case 0:
				drawImage_Background(canvas, actual_pixel, x, y);
				break;
			case 1:
				drawImage_Player(canvas, actual_pixel, x, y);
				break;
			}
		}
	}
}

void drawToCanvas(GamesEngineeringBase::Window* canvas, int x, int y, unsigned char colour[4]) {
	if (colour[3] > 0) {
		for (int i = 0; i < 3; i++) {
			colour[i] = colour[i] * colour[3] / 255;
		}
		canvas->draw(x, y, colour);
	}
}

void Scene::drawImage_Background(GamesEngineeringBase::Window* canvas, int actual_pixel[2], int x, int y) {
	// Fake Background: dot every 50 pixels
	if (actual_pixel[0] % 50 == 0 && actual_pixel[1] % 50 == 0) {
		canvas->draw(x, y, 0, 255, 0);
	}
	// Background: Tiles
	unsigned char temp_colour[4]{};
	background.getPixelColour(actual_pixel, temp_colour);
	drawToCanvas(canvas, x, y, temp_colour);
}

void Scene::drawImage_Player(GamesEngineeringBase::Window* canvas, int actual_pixel[2], int x, int y) {
	if (player.image.isInside(actual_pixel[0], actual_pixel[1])) {
		unsigned char temp_colour[4]{};
		player.image.getPixelColour(actual_pixel, temp_colour);
		drawToCanvas(canvas, x, y, temp_colour);
	}
}

void Scene::drawImage_Enemies(GamesEngineeringBase::Window* canvas, int world_pixel[2]) {
	for (int i = 0; i < enemy_count; i++) {
		enemies[i].drawImage(canvas, world_pixel, height, width);
	}
}

void Scene::drawImage(GamesEngineeringBase::Window* canvas) {
	// Background -> Player -> Enemies -> Player Projectiles -> Enemy Projectiles -> Effects (if any)
	int world_pixel[2];
	world_pixel[0] = camera.getPosition(0) - width / 2;
	world_pixel[1] = camera.getPosition(1) - height / 2;
	drawImage_PerPixel(canvas, 0, world_pixel);  // Background
	drawImage_PerPixel(canvas, 1, world_pixel);  // Player
	drawImage_Enemies(canvas, world_pixel);  // Enemies
}

void Scene::update(updateData update_data) {
	total_time_elapsed += update_data.delta;
	// Player & Camera routine
	player.update(update_data);  // Handles enemy collisions and attacks
	int destination[2];
	player.getCoordinates(destination);
	camera.updatePosition(destination, update_data.delta);
	// Enemy routine
	enemy_spawn_timer -= update_data.delta;
	if (enemy_spawn_timer <= 0.0f) {
		spawnEnemy();
		int array_index = total_time_elapsed / GameParameters::Enemies::chunk_time_level_1;
		if (array_index >= GameParameters::Enemies::spawn_time_array_length_level_1) {
			array_index = GameParameters::Enemies::spawn_time_array_length_level_1 - 1;
		}
		enemy_spawn_timer += GameParameters::Enemies::spawn_time_per_chunk_level_1[array_index];
	}
	for (int i = 0; i < enemy_count; i++) {
		enemies[i].update(update_data, destination);
	}
	cleanUpEnemies();
}

void Scene::loadSprite(int i, std::string filename) {
	if (i == 0) {
		player.image.image.load(filename);
	}
	if (i == 1) {
		background.loadAllTiles();
	}
	if (i == 2) {
		enemies[0].loadSprite();
	}
}

void Scene::spawnEnemy() {
	if (enemy_count >= GameParameters::Enemies::max_enemy_count) {
		return;
	}
	// Spawn in 2x2 window size, then coinflip determines either corners or sides.
	// Corners simply add or subtract width or height divided by 2.
	// Sides "rotate" clockwise to their corresponding side.
	int spawn_position[2] { distribution_width_enemy(*random_engine) + camera.getPosition(0), 
							distribution_height_enemy(*random_engine) + camera.getPosition(1) };
	while (spawn_position[0] > camera.getPosition(0) - width / 2 - (int)(enemy_sprites[0].image.width)
		   && spawn_position[0] < camera.getPosition(0) + width / 2 + (int)(enemy_sprites[0].image.width)
		   && spawn_position[1] > camera.getPosition(1) - height / 2 - (int)(enemy_sprites[0].image.height)
		   && spawn_position[1] < camera.getPosition(1) + height / 2 + (int)(enemy_sprites[0].image.height)) {
		spawn_position[0] = distribution_width_enemy(*random_engine) + camera.getPosition(0);
		spawn_position[1] = distribution_height_enemy(*random_engine) + camera.getPosition(1);
	}
#ifdef _DEBUG
	std::print("spawn location: {0}, {1}\n", spawn_position[0] - camera.getPosition(0), spawn_position[1] - camera.getPosition(1));
#endif
	enemies[enemy_count] = Enemy(&(enemy_sprites[0]), spawn_position);
	enemy_count++;
}

void Scene::cleanUpEnemies() {
	int killed = 0;
	for (int i = 0; i < enemy_count; i++) {
		while (enemies[i].getHealth() <= 0 && i < enemy_count) {
			killed++;
			enemies[i] = enemies[enemy_count - killed];
			enemy_count--;
		}
	}
}