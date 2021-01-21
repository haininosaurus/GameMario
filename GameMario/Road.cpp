#include "Road.h"
#include "Utils.h"

void CRoad::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CRoad::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (type == 0)
	{
		l = x;
		t = y;
		r = x + INTRO_ROAD_BBOX_WIDTH;
		b = y + INTRO_ROAD_BBOX_HEIGHT;
	}
	if (type == 1)
	{
		l = x;
		t = y;
		r = x + ROAD_BBOX_WIDTH;
		b = y + ROAD_BBOX_HEIGHT;
	}



}

void CHeadRoad::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CHeadRoad::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + ROAD_BBOX_WIDTH;
	b = y + ROAD_BBOX_HEIGHT;
}