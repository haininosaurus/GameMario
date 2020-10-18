#include "Pipe.h"
#include "Utils.h"

void CPipe::Render() {
	renderBlock(NULL, 2, 3, 368, 101);
}

void CPipe::renderBlock(INT color, int w, int h, int x, int y)
{
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (i == 0) {
				if (j == 0) 	animation_set->at(0)->Render(x + SIZE * j, y + SIZE * i);
				else animation_set->at(1)->Render(x + SIZE * j, y + SIZE * i);
			}
			else {
				if (j == 0) 	animation_set->at(2)->Render(x + SIZE * j + 1, y + SIZE * i);
				else animation_set->at(3)->Render(x + SIZE * j, y + SIZE * i);
			}
		}
	}
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PIPE_BBOX_WIDTH;
	b = y + PIPE_BBOX_HEIGHT;
	DebugOut(L"w: %d\n", w);
}