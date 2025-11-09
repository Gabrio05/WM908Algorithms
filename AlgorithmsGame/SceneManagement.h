#ifndef SCENEMANAGE
#define SCENEMANAGE
#include <random>
#include <fstream>
#include "Player.h"
#include "GameParameters.h"
#include "GameBase/GamesEngineeringBase.h"
#include "UpdateData.h"
#include "Camera.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"

/* One scene entity per scene. Each level is a separate scene. */
class Scene {
	Camera camera{};
	int width = GameParameters::window_width;
	int height = GameParameters::window_height;
	float total_time_elapsed = 0.0f;
	Player player;
	int enemy_count = 0;
	int total_kills = 0;
	float enemy_spawn_timer[GameParameters::Enemies::unique_enemies]{};
	Background background{};
	Sprite* enemy_sprites;
	int projectile_count = 0;
	Sprite* projectile_sprites;
	std::mt19937* random_engine;
	std::uniform_int_distribution<> distribution_width_enemy{ -width * 2, width * 2 };
	std::uniform_int_distribution<> distribution_height_enemy{ -height * 2, height * 2 };

	// Drawing Functions
	// Background -> Player -> Enemies -> Player Projectiles -> Enemy Projectiles -> Effects (if any)
	void drawImage_PerPixel(GamesEngineeringBase::Window*, int index_function, int world_pixel[2]);
	void drawImage_Background(GamesEngineeringBase::Window*, int actual_pixel[2], int x, int y);
	void drawImage_Player(GamesEngineeringBase::Window*, int actual_pixel[2], int x, int y);
	void drawImage_Enemies(GamesEngineeringBase::Window*, int world_pixel[2]);
	void drawImage_Projectiles(GamesEngineeringBase::Window*, int world_pixel[2]);

	void spawnEnemyRoutine(float delta);
	void throwEnemyProjectilesRoutine(float delta);
public:
	Enemy* enemies;  // Enemy order is not guarranteed
	Projectile* projectiles;  // idem for projectiles
	float average_fps = 0;
	Scene();
	Scene(std::mt19937* engine);
	~Scene();
	Scene& operator=(const Scene&) = delete;
	Scene(const Scene&) = delete;

	void setFixedWorld();
	const int getEnemyNumber() { return enemy_count; }
	const int getProjectileNumber() { return projectile_count; }
	const int getTotalTimeElapsed() { return total_time_elapsed; }
	const int getTotalKills() { return total_kills; }
	void checkCollision(Collision* collision, int enemy_number, float delta);
	void checkProjectileCollision(Collision* collision, int enemy_number, float delta);
	void drawImage(GamesEngineeringBase::Window* canvas);
	void update(updateData update_data);  // Frame update loop, must call update function of all active entities in scene
	void loadSprite(int i, int j, std::string filename);  // Player, background, projectiles, and enemies on i, j for specific sprite
	void loadMap(std::string filename);
	void spawnEnemy(int enemy_number);  // Takes in the enemy_id type
	void throwProjectile(bool is_friendly, float pos[2], int attack_damage);
	void throwProjectile(bool is_friendly, float pos[2], int attack_damage, float vel[2]);
	void friendlyProjectileLateUpdate(int i, float delta);
	void cleanUpEnemies();
	void cleanUpProjectiles();
};

#endif
