#include "BackgroundObject.h"
#include "Game.h"
#include "Sprites.h"
#include "Utils.h"

void CBackgroundObject::Render() {

	animation_set->at(0)->Render(x, y);
	if (x == 2496 && y == 133) {
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 21; j++) {
				if (x + 16 * j == 2496) animation_set->at(0)->Render(x + 16 * j, y - 16 * i);
				else animation_set->at(1)->Render(x + 16 * j, y - 16 * i);
			}
		}
	}
}

void CBackgroundObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = 0; 
	b = 0;
}