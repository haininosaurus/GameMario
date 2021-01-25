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

#define CARD_AMOUNT						3

#define BOARD_TIME_X_PLUS				152.0f
#define BOARD_TIME_Y_PLUS				185.0f
#define BOARD_SCORE_X_PLUS				80.0f
#define BOARD_SCORE_Y_PLUS				185.0f
#define BOARD_ARROW_X_PLUS				80.0f
#define BOARD_ARROW_Y_PLUS				176.0f
#define BOARD_COIN_X_PLUS				160.0f
#define BOARD_COIN_Y_PLUS				176.0f
#define BOARD_LIVE_X_PLUS				56.0f
#define BOARD_LIVE_Y_PLUS				185.0f
#define BOARD_CARD_1_X_PLUS				200.0f
#define BOARD_CARD_2_X_PLUS				232.0f
#define BOARD_CARD_3_X_PLUS				264.0f
#define BOARD_CARD_Y_PLUS				171.0f

#define BOARD_CAM_X_PLUS				8.0f
#define BOARD_CAM_Y_PLUS				165.0f


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
	CScoreBoard() {
		cam = NULL; time = NULL; score = NULL; arrows = NULL;
		coin = NULL;
		lives = NULL;
		for (int i = 0; i < CARD_AMOUNT; i++)
		{
			card[i] = NULL;
		}
	}
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

