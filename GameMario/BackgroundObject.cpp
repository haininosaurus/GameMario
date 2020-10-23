#include "BackgroundObject.h"
#include "Game.h"
#include "Sprites.h"
#include "Utils.h"

void CBackgroundObject::Render() {

	animation_set->at(0)->Render(x, y);
}

void CBackgroundObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = 0; 
	b = 0;
}