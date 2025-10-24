#ifndef SCENEMANAGE
#define SCENEMANAGE
#include "GameParameters.h"
#include "GameBase/GamesEngineeringBase.h"
#include "Player.h"
#include "UpdateData.h"
#include "Camera.h"
#include "Background.h"

/* One scene entity per scene. Each level is a separate scene. */
class Scene {
	Camera camera;
	int width = GameParameters::window_width;
	int height = GameParameters::window_height;
	Player player;
	Background background;
public:
	Scene();
	void getPixelColour(int cameraPixel[2], unsigned char returnColour[3]);  // Automatically translates camera pixel to world pixel
	void update(updateData update_data);  // Frame update loop, must call update function of all active entities in scene
	void loadSprite(int i, std::string filename);  // Index 0
};

#endif
