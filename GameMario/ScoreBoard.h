#pragma once
#include "GameObject.h"
#include "Camera.h"

class CScoreBoard : public CGameObject
{
	CCamera* cam;
public:
	CScoreBoard() { cam = NULL; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetCam(CCamera* c) { cam = c; }
};

