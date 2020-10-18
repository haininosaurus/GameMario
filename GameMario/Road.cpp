#include "Road.h"
#include "Utils.h"

void CRoad::Render()
{

	if (x >= 640 && x <= 1104 && y==149)
	{
		animation_set->at(1)->Render(x, y);
	}
	else {
		animation_set->at(0)->Render(x, y);
	}

	RenderBoundingBox();
}

void CRoad::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}