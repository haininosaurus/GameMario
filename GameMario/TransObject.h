#pragma once
#include "GameObject.h"

#define TRANS_BBOX_WIDTH 16
#define TRANS_BBOX_HEIGHT 16

class CTransObject : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

