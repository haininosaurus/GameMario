#pragma once
#include "GameObject.h"

#define ROAD_BBOX_WIDTH  16
#define ROAD_BBOX_HEIGHT 16

#define INTRO_ROAD_BBOX_WIDTH	32
#define INTRO_ROAD_BBOX_HEIGHT	37

class CRoad : public CGameObject
{
	int type;
public:
	CRoad(int t) { type = t; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class CHeadRoad : public CGameObject
{
public:

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};