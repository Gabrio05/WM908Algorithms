#include "SceneManagement.h"
#ifdef _DEBUG
#include <print>
#endif

Scene::Scene() : player{this} {
	enemy_sprites = new Sprite[GameParameters::Enemies::unique_enemies]{};
	enemies = new Enemy[GameParameters::Enemies::max_enemy_count]{};
	projectile_sprites = new Sprite[GameParameters::Projectiles::unique_friendly_sprites + GameParameters::Projectiles::unique_enemy_sprites]{};
	projectiles = new Projectile[GameParameters::Projectiles::max_projectile_count]{};
	for (int i = 0; i < GameParameters::Enemies::unique_enemies; i++) {
		enemy_spawn_timer[i] = GameParameters::Enemies::global_spawn_time_per_chunk_level_1[i][0];
	}
	random_engine = nullptr;
}

Scene::Scene(std::mt19937* engine) : player{ this }, random_engine{ engine } {
	enemy_sprites = new Sprite[GameParameters::Enemies::unique_enemies]{};
	enemies = new Enemy[GameParameters::Enemies::max_enemy_count]{};
	projectile_sprites = new Sprite[GameParameters::Projectiles::unique_friendly_sprites + GameParameters::Projectiles::unique_enemy_sprites]{};
	projectiles = new Projectile[GameParameters::Projectiles::max_projectile_count]{};
	for (int i = 0; i < GameParameters::Enemies::unique_enemies; i++) {
		enemy_spawn_timer[i] = GameParameters::Enemies::global_spawn_time_per_chunk_level_1[i][0];
	}
}

Scene::~Scene() {
	delete[] enemy_sprites;
	delete[] enemies;
	delete[] projectile_sprites;
	delete[] projectiles;
}

int readIntNumber(std::ifstream* file) {
	int number = 0;
	bool negative = false;
	while (!file->eof()) {
		char c = file->get();
		if (c == ',') {
			break;
		}
		else if (c == '-') {
			negative = true;
		}
		else {
			number *= 10;
			number += c - '0';
		}
	}
	if (negative) {
		return -number;
	}
	return number;
}

float readNumber(std::ifstream* file) {
	int whole_part = 0;
	bool negative = false;
	int decimal_part = 0;
	bool on_decimals = false;
	int decimal_digits = 0;
	bool exponential = false;
	bool negative_exponent = false;
	int exponent = 0;
	while (!file->eof()) {
		char c = file->get();
		if (c == ',') {
			break;
		}
		else if (c == '.') {
			on_decimals = true;
		}
		else if (c == 'e') {
			exponential = true;
		}
		else if (c == '-') {
			if (exponential) {
				negative_exponent = true;
			}
			else {
				negative = true;
			}
		}
		else {
			if (!on_decimals) {
				whole_part *= 10;
				whole_part += c - '0';
			}
			else if (!exponential) {
				decimal_part *= 10;
				decimal_part += c - '0';
				decimal_digits++;
			}
			else {
				exponent *= 10;
				exponent += c - '0';
			}
		}
	}
	float number = whole_part + decimal_part / pow(10, decimal_digits);
	if (exponential) {
		if (negative_exponent) {
			exponent = -exponent;
		}
		number = number * pow(10, exponent);
	}
	if (negative) {
		return -number;
	}
	return number;
}

void Scene::saveGame() {
	// Saves the current stage of the game. All numbers are separated by ',' even at the end of a line.
	// Line breaks have been inserted every so often for txt readability, do not forget to file.get() for each!
	std::ofstream file;
	file.open(GameParameters::save_filename);
	// Camera
	file << camera.getPosition(0) << ',' << camera.getPosition(1) << ',' << '\n';
	// Scene Variables
	file << total_time_elapsed << ',';
	file << enemy_count << ',';
	file << total_kills << ',';
	file << projectile_count << ',' << '\n';
	for (int i = 0; i < GameParameters::Enemies::unique_enemies; i++) {
		file << enemy_spawn_timer[i] << ',';
	}
	file << '\n';
	file << background.isWorldFixed() << ',' << '\n';
	// Player
	player.saveToSave(&file);
	// Enemies
	for (int i = 0; i < enemy_count; i++) {
		file << enemies[i].getPosition(0) << ',';
		file << enemies[i].getPosition(1) << ',';
		file << enemies[i].getHealth() << ',';
		file << enemies[i].getSpeed() << ',';
		file << enemies[i].is_throwing_projectiles << ',';
		file << enemies[i].projectile_delay << ',';
		file << enemies[i].attack.damage << ',';
		file << enemies[i].enemy_type << ',';
		file << '\n';
	}
	// Projectiles
	for (int i = 0; i < projectile_count; i++) {
		file << projectiles[i].getPosition(0) << ',';
		file << projectiles[i].getPosition(1) << ',';
		file << projectiles[i].getVelocityMove() << ',';
		file << projectiles[i].getVelocity(0) << ',';
		file << projectiles[i].getVelocity(1) << ',';
		file << projectiles[i].getLifespan() << ',';
		file << projectiles[i].friendliness() << ',';
		file << projectiles[i].attack.damage << ',';
		file << '\n';
	}
	file.close();
}

void Scene::loadGame() {
	std::ifstream file;
	int digits[2];
	float numbers[2];
	file.open(GameParameters::save_filename);
	// Camera
	digits[0] = readIntNumber(&file);
	digits[1] = readIntNumber(&file);
	camera = Camera(digits);
	file.get();
	// Scene Variables
	numbers[0] = readNumber(&file);
	total_time_elapsed = numbers[0];
	digits[0] = readIntNumber(&file);
	enemy_count = digits[0];
	digits[0] = readIntNumber(&file);
	total_kills = digits[0];
	digits[0] = readIntNumber(&file);
	projectile_count = digits[0];
	file.get();
	for (int i = 0; i < GameParameters::Enemies::unique_enemies; i++) {
		numbers[0] = readNumber(&file);
		enemy_spawn_timer[i] = numbers[0];
	}
	file.get();
	digits[0] = readIntNumber(&file);
	if (digits[0] == 1) {
		setFixedWorld();
	}
	file.get();
	// Player
	float coord[2];
	coord[0] = readNumber(&file);
	coord[1] = readNumber(&file);
	int h = readIntNumber(&file);
	int sh = readIntNumber(&file);
	float inv = readNumber(&file);
	float shield_t = readNumber(&file);
	float at1 = readNumber(&file);
	float at2 = readNumber(&file);
	float at3 = readNumber(&file);
	float at3_vel[2];
	at3_vel[0] = readNumber(&file);
	at3_vel[1] = readNumber(&file);
	player.loadFromSave(coord, h, sh, inv, shield_t, at1, at2, at3, at3_vel);
	file.get();
	// Enemies
	for (int i = 0; i < enemy_count; i++) {
		numbers[0] = readNumber(&file);
		numbers[1] = readNumber(&file);
		digits[0] = readIntNumber(&file);
		digits[1] = readIntNumber(&file);
		int proj = readIntNumber(&file);
		float proj_del = readNumber(&file);
		int atk = readIntNumber(&file);
		int type = readIntNumber(&file);
		enemies[i] = Enemy(&(enemy_sprites[type]), numbers, type);
		enemies[i].setStats(digits[0], atk, digits[1]);
		enemies[i].is_throwing_projectiles = (bool)proj;
		enemies[i].projectile_delay = proj_del;
		file.get();
	}
	// Projectiles
	for (int i = 0; i < projectile_count; i++) {
		numbers[0] = readNumber(&file);
		numbers[1] = readNumber(&file);
		int vel_mov = readIntNumber(&file);
		float vel[2];
		vel[0] = readNumber(&file);
		vel[1] = readNumber(&file);
		float life = readIntNumber(&file);
		int friendly = readIntNumber(&file);
		digits[1] = readIntNumber(&file);
		Sprite* spr;
		if (friendly) {
			spr = &(projectile_sprites[0]);
		}
		else {
			spr = &(projectile_sprites[GameParameters::Projectiles::unique_friendly_sprites]);
		}
		if (vel_mov) {
			projectiles[i] = Projectile(spr, friendly, numbers, digits[1], vel);
		}
		else {
			projectiles[i] = Projectile(spr, friendly, numbers, digits[1]);
		}
		projectiles[i].setLifespan(life);
		file.get();
	}
	file.close();
}

void Scene::setFixedWorld() {
	background.setFixedWorld();
	player.setFixedWorld();
	int destination[2];
	player.getCoordinates(destination);
	camera = Camera(destination);
}

void Scene::checkCollision(Collision* collision, int enemy_number, float delta) {
	return enemies[enemy_number].checkCollision(collision, delta);
}

void Scene::checkProjectileCollision(Collision* collision, int enemy_number, float delta) {
	return projectiles[enemy_number].checkCollision(collision, delta);
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

void Scene::drawImage_Projectiles(GamesEngineeringBase::Window* canvas, int world_pixel[2]) {
	for (int i = 0; i < projectile_count; i++) {
		projectiles[i].drawImage(canvas, world_pixel, height, width);
	}
}

void Scene::drawImage(GamesEngineeringBase::Window* canvas) {
	// Background -> Player -> Enemies -> Projectiles -> Effects (if any)
	int world_pixel[2];
	world_pixel[0] = camera.getPosition(0) - width / 2;
	world_pixel[1] = camera.getPosition(1) - height / 2;
	drawImage_PerPixel(canvas, 0, world_pixel);  // Background
	drawImage_PerPixel(canvas, 1, world_pixel);  // Player
	drawImage_Enemies(canvas, world_pixel);  // Enemies
	drawImage_Projectiles(canvas, world_pixel);  // Projectiles
}

void Scene::update(updateData update_data) {
	total_time_elapsed += update_data.delta;
	// Player & Camera routine
	player.update(update_data);  // Handles enemy and projectile collisions and attacks
	int destination[2];
	player.getCoordinates(destination);
	camera.updatePosition(destination, update_data.delta);
	// Enemy routine
	spawnEnemyRoutine(update_data.delta);
	for (int i = 0; i < enemy_count; i++) {
		enemies[i].update(update_data, destination);
	}
	cleanUpEnemies();
	// Projectile routine
	throwEnemyProjectilesRoutine(update_data.delta);
	bool has_friendly_projectile = false;
	int decoy_destination[2];
	for (int i = 0; i < projectile_count; i++) {
		if (projectiles[i].friendliness()) {  // Haha, get decoyed
			has_friendly_projectile = true;
			decoy_destination[0] = projectiles[i].getPosition(0);
			decoy_destination[1] = projectiles[i].getPosition(1);
			break;
		}
	}
	if (!has_friendly_projectile) {
		decoy_destination[0] = destination[0];
		decoy_destination[1] = destination[1];
	}
	for (int i = 0; i < projectile_count; i++) {
		projectiles[i].update(update_data, decoy_destination);
	}
	if (has_friendly_projectile) {
		for (int i = 0; i < projectile_count; i++) {
			if (projectiles[i].friendliness()) {
				friendlyProjectileLateUpdate(i, update_data.delta);
			}
		}
	}
	cleanUpProjectiles();
}

void Scene::loadSprite(int i, int j, std::string filename) {
	if (i == 0) {
		player.image.image.load(filename);
	}
	else if (i == 1) {
		background.loadAllTiles();
	}
	else if (i == 2) {
		projectile_sprites[j].image.load(filename);
	}
	else if (i == 3) {
		enemy_sprites[j].image.load(filename);
	}
}

void Scene::loadMap(std::string filename) {
	int indices[GameParameters::Background::map_size[0] * GameParameters::Background::map_size[1]];
	std::ifstream file;
	file.open(filename);
	char ch;
	int line = -6;
	int i = 0;
	int buffer = -1;
	while (!file.eof()) {
		ch = file.get();
		if (ch == '\n') {
			i = 0;
			buffer = -1;
			line++;
			continue;
		}
		if (line < 0) {
			continue;
		}
		if (ch == ',') {
			indices[line * GameParameters::Background::map_size[0] + i] = buffer;
			buffer = -1;
			i++;
			continue;
		}
		if (buffer == -1) {
			buffer = ch - '0';
		}
		else {
			buffer *= 10;
			buffer += ch - '0';
		}
	}
	file.close();
	background.populateMap(indices);
}

void Scene::spawnEnemyRoutine(float delta) {
	for (int i = 0; i < GameParameters::Enemies::unique_enemies; i++) {
		enemy_spawn_timer[i] -= delta;
		if (enemy_spawn_timer[i] <= 0.0f) {
			spawnEnemy(i);
			int array_index = total_time_elapsed / GameParameters::Enemies::global_chunk_time_level_1[i];
			if (array_index >= GameParameters::Enemies::global_spawn_time_array_length_level_1[i]) {
				array_index = GameParameters::Enemies::global_spawn_time_array_length_level_1[i] - 1;
			}
			enemy_spawn_timer[i] += GameParameters::Enemies::global_spawn_time_per_chunk_level_1[i][array_index];
		}
	}
}

void Scene::spawnEnemy(int enemy_number) {
	if (enemy_count >= GameParameters::Enemies::max_enemy_count) {
		return;
	}
	// Spawn in 2x2 window size, then coinflip determines either corners or sides.
	// Corners simply add or subtract width or height divided by 2.
	// Sides "rotate" clockwise to their corresponding side.
	int spawn_position[2] { distribution_width_enemy(*random_engine) + camera.getPosition(0), 
							distribution_height_enemy(*random_engine) + camera.getPosition(1) };
	while (spawn_position[0] > camera.getPosition(0) - width / 2 - (int)(enemy_sprites[enemy_number].image.width)
		   && spawn_position[0] < camera.getPosition(0) + width / 2 + (int)(enemy_sprites[enemy_number].image.width)
		   && spawn_position[1] > camera.getPosition(1) - height / 2 - (int)(enemy_sprites[enemy_number].image.height)
		   && spawn_position[1] < camera.getPosition(1) + height / 2 + (int)(enemy_sprites[enemy_number].image.height)) {
		spawn_position[0] = distribution_width_enemy(*random_engine) + camera.getPosition(0);
		spawn_position[1] = distribution_height_enemy(*random_engine) + camera.getPosition(1);
	}
#ifdef _DEBUG
	std::print("spawn location: {0}, {1}\n", spawn_position[0] - camera.getPosition(0), spawn_position[1] - camera.getPosition(1));
#endif
	float spawn_pos[2];
	spawn_pos[0] = (float)spawn_position[0];
	spawn_pos[1] = (float)spawn_position[1];
	enemies[enemy_count] = Enemy(&(enemy_sprites[enemy_number]), spawn_pos, enemy_number);
	enemy_count++;
}

void Scene::cleanUpEnemies() {
	for (int i = 0; i < enemy_count; i++) {
		while (enemies[i].getHealth() <= 0 && i < enemy_count) {
			enemies[i] = enemies[enemy_count - 1];
			enemy_count--;
			total_kills++;
		}
	}
}

void Scene::throwEnemyProjectilesRoutine(float delta) {
	for (int i = 0; i < enemy_count; i++) {
		if (enemies[i].is_throwing_projectiles) {
			enemies[i].projectile_delay -= delta;
			if (enemies[i].projectile_delay <= 0) {
				float pos[2];
				pos[0] = (float)enemies[i].getPosition(0);
				pos[1] = (float)enemies[i].getPosition(1);
				throwProjectile(false, pos, enemies[i].attack.damage);
				enemies[i].projectile_delay += GameParameters::Projectiles::enemy_delay;
			}
		}
	}
}

void Scene::throwProjectile(bool is_friendly, float pos[2], int attack_damage) {
	if (projectile_count > GameParameters::Projectiles::max_projectile_count) {
		if (!is_friendly) { return; }
		bool cleaned = false;
		for (int i = 0; i < projectile_count; i++) {
			if (!projectiles[i].friendliness()) {
				projectiles[i] = projectiles[projectile_count - 1];
				projectile_count--;
				cleaned = true;
				break;
			}
		}
		if (!cleaned) { return; }
	}
	Sprite* spr;
	if (is_friendly) {
		spr = &(projectile_sprites[0]);
	}
	else {
		spr = &(projectile_sprites[GameParameters::Projectiles::unique_friendly_sprites]);
	}
	projectiles[projectile_count] = Projectile(spr, is_friendly, pos, attack_damage);
	projectile_count++;
}

void Scene::throwProjectile(bool is_friendly, float pos[2], int attack_damage, float vel[2]) {
	if (projectile_count > GameParameters::Projectiles::max_projectile_count) {
		if (!is_friendly) { return; }
		bool cleaned = false;
		for (int i = 0; i < projectile_count; i++) {
			if (!projectiles[i].friendliness()) {
				projectiles[i] = projectiles[projectile_count - 1];
				projectile_count--;
				cleaned = true;
				break;
			}
		}
		if (!cleaned) { return; }
	}
	Sprite* spr;
	if (is_friendly) {
		spr = &(projectile_sprites[0]);
	}
	else {
		spr = &(projectile_sprites[GameParameters::Projectiles::unique_friendly_sprites]);
	}
	projectiles[projectile_count] = Projectile(spr, is_friendly, pos, attack_damage, vel);
	projectile_count++;
}

void Scene::friendlyProjectileLateUpdate(int friendly_index, float delta) {
	Collision* col = projectiles[friendly_index].getCollisionPointer();
	for (int i = 0; i < projectile_count; i++) {
		if (!projectiles[i].friendliness()) {
			projectiles[i].checkCollision(col, delta);
			if (col->has_collision_occured) {
				projectiles[i].is_used = true;
			}
		}
	}
	for (int i = 0; i < enemy_count; i++) {
		enemies[i].checkCollision(col, delta);
		if (col->has_collision_occured) {
			enemies[i].takeDamage(&projectiles[i].attack);
			projectiles[friendly_index].is_used = true;
		}
	}
}

void Scene::cleanUpProjectiles() {
	for (int i = 0; i < projectile_count; i++) {
		while (projectiles[i].is_used && i < projectile_count) {
			projectiles[i] = projectiles[projectile_count - 1];
			projectile_count--;
		}
	}
}