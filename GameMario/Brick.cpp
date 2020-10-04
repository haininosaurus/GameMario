#include "Brick.h"


CBrick::CBrick(float x, float y, LPDIRECT3DTEXTURE9 texBrick):CGameObject(x, y, texBrick) {};

void CBrick::Render(){
	CGameObject::Render();
}