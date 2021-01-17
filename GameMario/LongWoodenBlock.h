#pragma once
#include "GameObject.h"

#define LONG_WOODEN_BLOCK_BBOX_WIDTH 48
#define LONG_WOODEN_BLOCK_BBOX_HEIGHT 16

class CLongWoodenBlock : public CGameObject
{
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

