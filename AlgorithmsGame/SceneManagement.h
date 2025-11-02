#ifndef SCENEMANAGE
#define SCENEMANAGE

#include <functional>

#include "Player.h"
#include "GameParameters.h"
#include "GameBase/GamesEngineeringBase.h"
#include "UpdateData.h"
#include "Camera.h"
#include "Background.h"
#include "Enemy.h"

/* One scene entity per scene. Each level is a separate scene. */
class Scene {
	Camera camera{};
	int width = GameParameters::window_width;
	int height = GameParameters::window_height;
	Player player;
	int enemy_count = 0;
	float enemy_spawn_timer = GameParameters::Enemies::initial_spawn_time;
	Background background{};
	Sprite* enemy_sprites;

	// Drawing Functions
	// Background -> Player -> Enemies -> Player Projectiles -> Enemy Projectiles -> Effects (if any)
	void drawImage_PerPixel(GamesEngineeringBase::Window*, int index_function, int world_pixel[2]);
	void drawImage_Background(GamesEngineeringBase::Window*, int actual_pixel[2], int x, int y);
	void drawImage_Player(GamesEngineeringBase::Window*, int actual_pixel[2], int x, int y);
	void drawImage_Enemies(GamesEngineeringBase::Window*, int world_pixel[2]);
public:
	Enemy* enemies;  // Enemy order is not guarranteed
	Scene();
	~Scene();
	Scene& operator=(const Scene&) = delete;
	Scene(const Scene&) = delete;

	int getEnemyNumber();
	void checkCollision(Collision* collision, int enemy_number, float delta);
	void drawImage(GamesEngineeringBase::Window* canvas);
	//void getPixelColour(int cameraPixel[2], unsigned char returnColour[3]);  // Automatically translates camera pixel to world pixel
	void update(updateData update_data);  // Frame update loop, must call update function of all active entities in scene
	void loadSprite(int i, std::string filename);  // Index 0
	void spawnEnemy();
	void cleanUpEnemies();
};

#endif
