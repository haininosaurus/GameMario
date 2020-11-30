#pragma once
#include "GameObject.h"

#define STATIC_OBJECT_BBOX_WIDTH 16
#define STATIC_OBJECT_BBOX_HEIGHT 16

class CStaticObject : public CGameObject
{
	int type;
public:
	CStaticObject(int t) { type = t; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

