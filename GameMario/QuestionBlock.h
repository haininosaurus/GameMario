#pragma once
#include "GameObject.h"

class CQuestionBlock : public CGameObject
{
public:
	CQuestionBlock(float x, float y);
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

