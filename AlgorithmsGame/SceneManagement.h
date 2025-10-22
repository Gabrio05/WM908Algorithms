#ifndef SCENEMANAGE
#define SCENEMANAGE
#include "GameParameters.h"
#include "GameBase/GamesEngineeringBase.h"
#include "SpriteHandler.h"
#include "Player.h"
#include "UpdateData.h"

class Camera {
	float position[2];
	float time_to_destination = GameParameters::Camera::time_to_destination;
public:
	Camera();  // Camera at position 0,0
	Camera(int[2]);  // Length 2 array to set x and y of camera
	void updatePosition(int destination[2], float t);  // Smooth interpolation to target based on t in [0, 1]
	int getPosition(int i);  // i = 0 for x, i = 1 for y
};

class Scene {
	Camera camera;
	int width = GameParameters::window_width;
	int height = GameParameters::window_height;
	Player player;
public:
	Scene();
	void getPixelColour(int cameraPixel[2], int returnColour[3]);  // From camera pixel to world pixel
	void update(UpdateData update_data);
	void loadSprite(int i, std::string fileName);  // Index 0
};

#endif
