#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Mario.h"

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

