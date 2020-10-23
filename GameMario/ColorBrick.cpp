#include "ColorBrick.h"

void CColorBrick::Render(){
	animation_set->at(0)->Render(x, y);

}

void CColorBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COLOR_BRICK_BBOX_WIDTH;
	b = y + COLOR_BRICK_BBOX_HEIGHT;
}

void CColorBrickTop::Render() {
	animation_set->at(0)->Render(x, y);

}

void CColorBrickTop::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COLOR_BRICK_BBOX_WIDTH;
	b = y + COLOR_BRICK_BBOX_HEIGHT;
}