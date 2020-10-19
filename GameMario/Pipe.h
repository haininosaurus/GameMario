#pragma once
#include "GameObject.h"

#define PIPE_BBOX_WIDTH 16
#define PIPE_BBOX_HEIGHT 16

#define SIZE 16
class CPipe : public CGameObject
{
	int h;
	int w;
	INT checkHead;

public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void renderBlock(INT checkHead, int w, int h, int x, int y);
};

