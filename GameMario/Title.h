#pragma once
#include "GameObject.h"

#define TITLE_SPEED_Y			0.2f

#define DARK_TITLE			0
#define LIGHT_TITLE			1
#define SELECT_ONE_TITLE	2
#define SELECT_TWO_TITLE	3

#define HIDEN_TITLE			4

class CTitle : public CGameObject
{
	int type;
	int form;
	DWORD create_time;
public:
	CTitle(int f);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	void SetType(int t) { type = t; }
	int GetType() { return type; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }
	void CreateIntroAnimationTitle();
};

