#pragma once
#include "GameObject.h"
#include "Collision.h"

#define PIRANHAPLANT_SPEECH_Y			0.035f

#define PIRANHAPLANT_STATE_HIDE					1
#define PIRANHAPLANT_STATE_APPEARANCE			2
#define PIRANHAPLANT_STATE_MOVE_UP				3
#define PIRANHAPLANT_STATE_MOVE_DOWN			4



#define PIRANHAPLANT_BBOX_WIDTH			16
#define PIRANHAPLANT_BBOX_HEIGHT		22

class CPiranhaPlant : public CGameObject
{
	float sx, sy, tan;
	float y_limit;

	int move_up_state;
	int move_down_state;
	int appearance_state;
	int hide_state;
	bool check_y_limit;
	bool found_player;

	DWORD move_up_time;
	CGameObject* player;


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
	virtual LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);

public:
	CPiranhaPlant() {};
	CPiranhaPlant(CGameObject* mario);
	virtual void SetState(int state);
	virtual int GetState();
};

