#pragma once
#include "GameObject.h"
#include "Collision.h"

#define FIREPIRANHAPLANT_SPEECH_Y			0.035f

#define FIREPIRANHAPLANT_STATE_HIDE					1
#define FIREPIRANHAPLANT_STATE_APPEARANCE			2
#define FIREPIRANHAPLANT_STATE_MOVE_UP				3
#define FIREPIRANHAPLANT_STATE_MOVE_DOWN			4

#define FIREPIRANHAPLANT_ANI_DOWN_LEFT				0
#define FIREPIRANHAPLANT_ANI_TOP_LEFT				1
#define FIREPIRANHAPLANT_ANI_DOWN_RIGHT				2
#define FIREPIRANHAPLANT_ANI_TOP_RIGHT				3


#define FIREPIRANHAPLANT_BBOX_WIDTH			16
#define FIREPIRANHAPLANT_BBOX_HEIGHT		33


class CFirePiranhaPlant : public CollisionObject
{
	float sx, sy, tan;
	float y_limit;

	int move_up_state;
	int move_down_state;
	int appearance_state;
	int hide_state;
	bool is_shoot;
	bool check_y_limit;
	bool found_player;

	int down_left_state;
	int down_right_state;
	int top_right_state;
	int top_left_state;
	DWORD move_up_time;
	DWORD shoot_start;
	CGameObject* player;
	CGameObject* fire_plant_bullet;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

	
public:
	void CreateFirePlantBullet(CGameObject* fireplantbullet);
	void ShootFirePlantBullet();
	CFirePiranhaPlant(CGameObject* mario);
	virtual void SetState(int state);
	virtual int GetState();
};

