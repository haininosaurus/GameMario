#include "Road.h"
#include "Utils.h"

void CRoad::Render()
{

	if (x >= 640 && x <= 1104 && y==149)
	{
		animation_set->at(1)->Render(x, y);
	}
	else {
		if(x == 0 && y == 149 
		|| x == 640 && y == 133
		|| x == 1168 && y == 149
		|| x == 1552 && y == 149
		|| x == 1680 && y == 149
		|| x == 2272 && y == 149)
			animation_set->at(2)->Render(x, y);
		else if(x == 624 && y == 149
			|| x == 1088 && y == 133
			|| x == 1504 && y == 149
			|| x == 1616 && y == 149
			|| x == 2240 && y == 149
			|| x == 2816 && y == 149)
				animation_set->at(4)->Render(x, y);
		else if(x == 640 && y == 149)
			animation_set->at(3)->Render(x, y);
		else if(x == 1088 && y == 149)
			animation_set->at(5)->Render(x, y);
		else animation_set->at(0)->Render(x, y);
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