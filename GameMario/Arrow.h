#pragma once
#include"GameObject.h"
#include "Utils.h"

#define ARROW_STATE_WHITE		0
#define ARROW_STATE_BLACK		1
#define ARROW_STATE_WHITE_P		2
#define ARROW_STATE_BLACK_P		3

#define ARROW_ANI_WHITE			0
#define ARROW_ANI_BLACK			1
#define ARROW_ANI_WHITE_P		2
#define ARROW_ANI_BLACK_P		3

#define ARROW_POS_X_PLUS_8		8
#define ARROW_POS_X_PLUS_16		16
#define ARROW_POS_X_PLUS_24		24
#define ARROW_POS_X_PLUS_32		32
#define ARROW_POS_X_PLUS_40		40
#define ARROW_POS_X_PLUS_48		48

#define ARROW_RESET_P_TIME		2500

class CArrow : public CGameObject
{
	int isP;
	int isBlack;
public:
	CArrow(int p) { isP = p; isBlack = 1; };
	void SetWhiteState() { isBlack = 0; }
	void SetBlackState() { isBlack = 1; }
	int GetIsBlack() { return isBlack; }
	int GetIsP() { return isP; }
	void SetState(int state);

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

class CArrows : public CGameObject
{
	vector<CArrow*> arrows;
	DWORD p_start;

public:

	CArrows(vector<CArrow*> arr) {
		p_start = 0;
		for (unsigned int i = 0; i < arr.size(); i++)
		{
			arrows.push_back(arr[i]);
		}

	}


	//void PushArrows(CArrow* num);
	void SetPositionArrows(float x, float y);
	void SetWhiteArrows();
	void SetBlackArrows();
	void SetPStart(DWORD t) { p_start = t; }

	void ResetArrows();

	int GetPState(){ return arrows[6]->GetIsBlack(); }

	virtual void Render() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};