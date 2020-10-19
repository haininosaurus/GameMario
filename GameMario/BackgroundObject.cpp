#include "BackgroundObject.h"
#include "Game.h"
#include "Sprites.h"
#include "Utils.h"

void CBackgroundObject::Render() {
	if (x == 16 && y >= 117 && y <= 133
		|| x == 96 && y == 117
		|| x == 976 && y == 101
		|| x == 848 && y == 101
		|| x == 1920 && y == 117) {
		animation_set->at(2)->Render(x, y);
	}
	else if (x == 80 && y == 133
		|| x == 32 && y == 117
		|| x == 112 && y == 117
		|| x == 992 && y == 101
		|| x == 864 && y == 101
		|| x == 896 && y == 101
		|| x == 1936 && y == 117) {
		animation_set->at(5)->Render(x, y);
	}
	else if (x == 96 && y == 133
		|| x == 48 && y == 117
		|| x == 32 && y == 101
		|| x == 976 && y == 117
		|| x == 848 && y == 117
		|| x == 880 && y == 101
		|| x == 912 && y == 101
		|| x == 896 && y == 85
		|| x == 1920 && y == 133) {
		animation_set->at(4)->Render(x, y);
	}
	else if (x == 16 && y == 101
		|| x == 32 && y == 85
		|| x == 64 && y == 101
		|| x == 96 && y == 101
		|| x == 960 && y == 117
		|| x == 976 && y == 85
		|| x == 832 && y == 117
		|| x == 848 && y == 85
		|| x == 880 && y == 85
		|| x == 928 && y == 85
		|| x == 896 && y == 69
		|| x == 1904 && y == 133
		|| x == 1920 && y == 101) {
		animation_set->at(0)->Render(x, y);
	}
	else if (x == 48 && y == 85
		|| x == 80 && y == 101
		|| x == 112 && y == 101
		|| x == 128 && y == 117
		|| x == 1008 && y == 101
		|| x == 992 && y == 85
		|| x == 864 && y == 85
		|| x == 912 && y == 69
		|| x == 944 && y == 85
		|| x == 1936 && y == 101
		|| x == 1952 && y == 117) {
		animation_set->at(1)->Render(x, y);
	}
	else if (x == 48 && y == 101
		|| x == 128 && y == 133
		|| x == 1008 && y == 117
		|| x == 944 && y == 117
		|| x == 944 && y == 101
		|| x == 912 && y == 85
		|| x == 1952 && y == 133) {
		animation_set->at(3)->Render(x, y);
	}
	else if (x == 160 && y == 133
		|| x == 176 && y == 133
		|| x == 192 && y == 133
		|| x == 736 &&	y == 117
		|| x == 752 && y == 117
		|| x == 768 && y == 117
		|| x == 688 && y == 117
		|| x == 704 && y == 117
		|| x == 720 && y == 117
		|| x == 1072 && y == 117
		|| x == 1056 && y == 117
		|| x == 1216 && y == 133
		|| x == 1232 && y == 133
		|| x == 1200 && y == 133
		|| x == 1744 && y == 133
		|| x == 1760 && y == 133
		|| x == 1776 && y == 133) {
		animation_set->at(7)->Render(x, y);
	}

	else if (x == 136 && y == 5
		|| x == 664 && y == 289
		|| x == 1192 && y == 289
		|| x == 2344 && y == 305) {
		DebugOut(L"load cloud \n");
		animation_set->at(9)->Render(x, y);
	}
	else if (x == 344 && y == -11) {
		DebugOut(L"load cloud \n");
		animation_set->at(8)->Render(x, y);
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