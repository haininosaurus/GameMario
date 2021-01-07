#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "TimePlay.h"
#include "Score.h"
#include "Arrow.h"
#include "Utils.h"
#include "CoinPlay.h"
#include "Lives.h"
#include "Cards.h"

#define CARD_AMOUNT			3

class CScoreBoard : public CGameObject
{
	CCamera* cam;
	CTime* time;
	CScore* score;
	CArrows* arrows;
	CCoinPlay* coin;
	CLives* lives;
	CCard* card[CARD_AMOUNT];

public:
	CScoreBoard() { cam = NULL; time = NULL; score = NULL; arrows = NULL; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetCam(CCamera* c) { cam = c; }
	void SetTime(CTime* t) { time = t; }
	void SetScore(CScore* s) { score = s; }
	void SetArrows(CArrows* a) { arrows = a; }
	void SetCoinPlay(CCoinPlay* c) { coin = c; }
	void SetLives(CLives* l) { lives = l; }
	void SetCards(CCard* c[CARD_AMOUNT]) {
		for (int i = 0; i < CARD_AMOUNT; i++)
		{
			card[i] = c[i];
		}
	}

	void SetWhiteArrows() { arrows->SetWhiteArrows(); }
	void SetBlackArrows() { arrows->SetBlackArrows(); }
};

