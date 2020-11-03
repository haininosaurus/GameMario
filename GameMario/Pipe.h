#pragma once
#include "GameObject.h"

#define PIPE_BBOX_WIDTH 15
#define PIPE_BBOX_HEIGHT 15

#define SIZE 16
class CPipe : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

