#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "TimePlay.h"
#include "Score.h"

class CScoreBoard : public CGameObject
{
	CCamera* cam;
	CTime* time;
	CScore* score;
public:
	CScoreBoard() { cam = NULL; time = NULL; score = NULL; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetCam(CCamera* c) { cam = c; }
	void SetTime(CTime* t) { time = t; }
	void SetScore(CScore* s) { score = s; }
};

