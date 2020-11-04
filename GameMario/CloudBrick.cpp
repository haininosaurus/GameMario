#include "CloudBrick.h"

void CCloudBrick::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CCloudBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CLOUD_BRICK_BBOX_WIDTH;
	b = y + CLOUD_BRICK_BBOX_HEIGHT;
}