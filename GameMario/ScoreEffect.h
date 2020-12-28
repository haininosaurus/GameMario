#pragma once
#include "GameObject.h"

#define SCORE_STATE_100				0
#define SCORE_STATE_200				1
#define SCORE_STATE_400				2
#define SCORE_STATE_800				3
#define SCORE_STATE_1000			4
#define SCORE_STATE_2000			5
#define SCORE_STATE_4000			6
#define SCORE_STATE_8000			7
#define SCORE_STATE_LEVELUP			8

#define SCORE_ANI_100				0
#define SCORE_ANI_200				1
#define SCORE_ANI_400				2
#define SCORE_ANI_800				3
#define SCORE_ANI_1000				4
#define SCORE_ANI_2000				5
#define SCORE_ANI_4000				6
#define SCORE_ANI_8000				7
#define SCORE_ANI_LEVELUP			8


#define SCORE_STATE_HIDEN			-1


#define SCORE_SPEED_Y				0.05f

class CScoreEffect : public CGameObject
{
	int score;
	int display_state;
	DWORD display_start;
public:
	CScoreEffect() { SetState(SCORE_STATE_HIDEN); }

	void SetState(int state);
	void DisplayScore(int score, float x, float y, DWORD t);

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

