#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_NORMAL	0
#define BRICK_STATE_HIDEN	1
#define BRICK_STATE_DESTROY	2

#define BRICK_ITEM_COIN				0
#define BRICK_ITEM_QUESTIONBLOCK	1

#define ITEM_AMOUNT		10

class CBrick : public CGameObject
{
	CGameObject* item[ITEM_AMOUNT];
public:
	void AddItemBrick(CGameObject* i);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};