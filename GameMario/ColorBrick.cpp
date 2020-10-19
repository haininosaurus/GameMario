#include "ColorBrick.h"

void CColorBrick::Render(){
	renderBlock(BLUE_BRICK, 4, 5, 272, 69);
	renderBlock(PINK_BRICK, 4, 3, 240, 101);
	renderBlock(WHITE_BRICK, 4, 7, 528, 37);
	renderBlock(PINK_BRICK, 4, 5, 480, 69);
	renderBlock(GREEN_BRICK, 5, 3, 416, 101);
	renderBlock(GREEN_BRICK, 6, 2, 528, 117);

	renderBlock(BLUE_BRICK, 7, 6, 1344, 53);
	renderBlock(PINK_BRICK, 7, 4, 1312, 85);
	renderBlock(GREEN_BRICK, 7, 2, 1280, 117);

	renderBlock(GREEN_BRICK, 3, 9, 2192, 5);
	renderBlock(PINK_BRICK, 3, 3, 2160, 101);
}

void CColorBrick::renderBlock(INT color, int w, int h, int x, int y)
{
	int size = 16;
	int brick = 9;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (i == 0) {
				if (j == 0) {
					animation_set->at(0 + brick * color)->Render(x + size * j, y + size * i);
					animation_set->at(36)->Render(x + size*w, y + size/2);
				}
				else if (j == w - 1) animation_set->at(2 + brick * color)->Render(x + size * j, y + size * i);
				else animation_set->at(1 + brick * color)->Render(x + size * j, y + size * i);

			}
			else if (i == h - 1) {
				if (j == 0) {
					animation_set->at(6 + brick * color)->Render(x + size * j, y + size * i);
					animation_set->at(37)->Render(x + size * w, y + size*i);
				}
				else if (j == w - 1) animation_set->at(8 + brick * color)->Render(x + size*j, y + size*i);
				else animation_set->at(7 + brick * color)->Render(x + size * j, y + size * i);
			}
			else {
				if (j == 0) {
					animation_set->at(3 + brick * color)->Render(x + size * j, y + size * i);
					animation_set->at(37)->Render(x + size * w, y + size*i);
				}
				else if (j == w - 1) animation_set->at(5 + brick * color)->Render(x + size * j, y + size * i);
				else animation_set->at(4 + brick * color)->Render(x + size * j, y + size * i);
			}
		}
	}
}

void CColorBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}