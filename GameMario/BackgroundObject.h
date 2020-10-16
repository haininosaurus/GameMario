#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "GameObject.h"

using namespace std;

class CBackgroundObject : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

