#include "ColorBrick.h"

void CColorBrick::Render(){
	renderBlock(0, 4, 5, 272, 69);
	renderBlock(1, 4, 3, 240, 101);
}

void CColorBrick::renderBlock(int color, int w, int h, int x, int y)
{
	int size = 16;
	int brick = 9;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (i == 0) {
				if (j == 0) 	animation_set->at(0 + brick*color)->Render(x + size * j, y + size * i);
				else if (j == w - 1) animation_set->at(2 + brick * color)->Render(x + size * j, y + size * i);
				else animation_set->at(1 + brick * color)->Render(x + size * j, y + size * i);
			}
			else if (i == h - 1) {
				if (j == 0) 	animation_set->at(6 + brick * color)->Render(x + size*j, y + size*i);
				else if (j == w - 1) animation_set->at(8 + brick * color)->Render(x + size*j, y + size*i);
				else animation_set->at(7 + brick * color)->Render(x + size * j, y + size * i);
			}
			else {
				if (j == 0) animation_set->at(3 + brick * color)->Render(x + size * j, y + size * i);
				else if (j == w - 1) animation_set->at(5 + brick * color)->Render(x + size * j, y + size * i);
				else animation_set->at(4 + brick * color)->Render(x + size * j, y + size * i);
			}
		}
	}
}

void CColorBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}