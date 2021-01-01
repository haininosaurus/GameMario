#pragma once
#include "GameObject.h"

#define QUESTIONBLOCK_BBOX_WIDTH  16
#define QUESTIONBLOCK_BBOX_HEIGHT 16

#define QUESTIONBLOCK_DEFLECT_SPEECH	0.125f
#define QUESTIONBLOCK_FALL_SPEECH		0.125f

#define QUESTIONBLOCK_ITEM_STATE		0
#define QUESTIONBLOCK_NORMAL_STATE		1
#define QUESTIONBLOCK_DEFLECT_STATE		2
#define QUESTIONBLOCK_FALL_STATE		3

#define QUESTION_COIN	0

#define ITEM_AMOUNT	10

class CQuestionBlock : public CGameObject
{
	DWORD deflect_start;
	bool check_init_location;
	float init_location_y;
	CGameObject* item[ITEM_AMOUNT];

public:
	CQuestionBlock() { 
		check_init_location = false;
		deflect_start = (DWORD)0.0f;
		init_location_y = 0.0f;
		for (int i = 0; i < ITEM_AMOUNT; i++)
			item[i] = NULL;
	}
	void AddItemQuestionBlock(CGameObject* item);
	void SetStateItem(int state);
	CGameObject* GetItemObject() {
		for (int i = 0; i < ITEM_AMOUNT; i++)
		{
			if (item[i] != NULL) return item[i];
		}
	}
	void SetDeflectStart(DWORD deflectstart) { deflect_start = deflectstart; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};

