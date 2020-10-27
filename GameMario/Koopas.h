#pragma once
#include "GameObject.h"

#define KOOPA_WALKING_SPEED 0.05f;
#define KOOPA_SPINNING_SPEED 0.15f;
#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HIDE_WIDTH 18
#define KOOPA_BBOX_HIDE_HEIGHT 16
#define KOOPA_BBOX_SPIN_WIDTH 16
#define KOOPA_BBOX_SPIN_HEIGHT 16

#define KOOPA_ANI_WALKING_LEFT 0
#define KOOPA_ANI_WALKING_RIGHT 1
#define KOOPA_ANI_HIDE 2
#define KOOPA_ANI_SPIN 3

#define KOOPA_STATE_WALKING_RIGHT 100
#define KOOPA_STATE_WALKING_LEFT 200
#define KOOPA_STATE_HIDE		300
#define KOOPA_STATE_SPIN_RIGHT	400
#define KOOPA_STATE_SPIN_LEFT	500

class CKoopa : public CGameObject
{
	int isSpin = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CKoopa();
	virtual void SetState(int state);
	virtual int GetState();
	//void SetSpin(int s) { isSpin == s; };
};

