#pragma once
#include "GameObject.h"

#define KOOPA_WALKING_SPEED 0.05f;
#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26

#define KOOPA_ANI_WALKING_LEFT 0
#define KOOPA_ANI_WALKING_RIGHT 1
#define KOOPA_STATE_WALKING_RIGHT 100
#define KOOPA_STATE_WALKING_LEFT 200

class CKoopa : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CKoopa();
	virtual void SetState(int state);
};

