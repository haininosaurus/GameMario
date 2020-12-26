#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "TimePlay.h"

class CScoreBoard : public CGameObject
{
	CCamera* cam;
	CTime* time;
public:
	CScoreBoard() { cam = NULL; time = NULL; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetCam(CCamera* c) { cam = c; }
	void SetTime(CTime* t) { time = t; }
};

