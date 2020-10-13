#include "Road.h"
#include "Utils.h"

void CRoad::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
	DebugOut(L"[INFO] Render brick successfully! \n");
}

void CRoad::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}