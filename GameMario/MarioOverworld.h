#pragma once
#include "GameObject.h"
#include "Node.h"
#include "Game.h"

#define MARIO_WALKING_SPEED						0.05f

#define MARIO_SMALL_BBOX_WIDTH					16
#define MARIO_SMALL_BBOX_HEIGHT					16

#define MARIO_STATE_IDLE						0
#define MARIO_STATE_MOVING_RIGHT				1
#define MARIO_STATE_MOVING_UP					2
#define MARIO_STATE_MOVING_LEFT					3
#define MARIO_STATE_MOVING_DOWN				4

#define MARIO_LEVEL_SMALL						0

class CMarioOverworld : public CGameObject
{
	vector<LPNODE> nodes;

	float destination_x;
	float destination_y;

	bool isMoving;
	int move_right;
	int move_top;
	int move_left;
	int move_bottom;
public:
	CMarioOverworld() {
		isMoving = false;

		move_right = 0; 
		move_top = 0;
		move_left = 0;
		move_bottom = 0;

		destination_x = 0;
		destination_y = 0;
	}
	void PushNode(CNode* node) {
		nodes.push_back(node);
	}
	void SetState(int state);
	bool GetIsMoving() { return isMoving; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};

