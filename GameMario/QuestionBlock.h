#pragma once
#include "GameObject.h"

#define QUESTIONBLOCK_BBOX_WIDTH  16
#define QUESTIONBLOCK_BBOX_HEIGHT 16

#define QUESTIONBLOCK_STATE_QUESTION 0
#define QUESTIONBLOCK_STATE_NORMAL 1

#define QUESTION_COIN	0

class CQuestionBlock : public CGameObject
{
	int iObj;
	vector<CGameObject>* quesObj;
public:
	//CQuestionBlock(int ques_id);
	virtual void Render();
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	//void SetState(int state);
};

