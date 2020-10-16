#include "BackgroundObject.h"
#include "Game.h"
#include "Sprites.h"


void CBackgroundObject::Render() {
	if (x == 16 && y >= 117 && y <= 133
		|| x == 96 && y == 117) {
		animation_set->at(2)->Render(x, y);
	}
	else if (x == 80 && y == 133
		|| x == 32 && y == 117
		|| x == 112 && y == 117) {
		animation_set->at(5)->Render(x, y);
	}
	else if (x == 96 && y == 133
		||x == 48 && y == 117
		||x == 32 && y == 101) {
		animation_set->at(4)->Render(x, y);
	}
	else if (x == 16 && y == 101
		|| x == 32 && y == 85
		|| x == 64 && y == 101
		|| x == 96 && y == 101) {
		animation_set->at(0)->Render(x, y);
	}
	else if (x == 48 && y == 85
		|| x == 80 && y == 101
		|| x == 112 && y == 101
		|| x == 128 && y == 117) {
		animation_set->at(1)->Render(x, y);
	}
	else if (x == 48 && y == 101
		|| x == 128 && y == 133) {
		animation_set->at(3)->Render(x, y);
	}
	else if (x == 160 && y == 133
		|| x == 176 && y == 133
		|| x == 192 && y == 133) {
		animation_set->at(7)->Render(x, y);
	}
	else animation_set->at(6)->Render(x, y);
}

void CBackgroundObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = 0; 
	b = 0;
}