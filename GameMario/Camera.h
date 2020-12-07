#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Mario.h"

#define WIDTH_MIN_MAP_1				0
#define WIDTH_MAX_MAP_1				2816
#define NEAR_WIDTH_LIMIT_MAP_1		2672

#define CAM_X_MAX					2520
#define CAM_X_MIN					0

#define UNDERGROUND_Y				165.0f
#define CAM_Y_UNDERGROUND			240.0f

class CCamera
{
	float cam_x, cam_y;
	float cx, cy;
	CMario* player;

public: 
	CCamera(CMario* p) {
		player = p; 
		cam_x = 0.0f;
		cam_y = 0.0f;
		cx = 0.0f;
		cy = 0.0f;
	}

	float GetCx() { return cam_x; }
	float GetCy() { return cam_y; }
	void SetCamPosition(float x, float y) { cam_x = x; cam_y = y; }
	void UpdateCam();
};

