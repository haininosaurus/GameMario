#pragma once
#include "GameObject.h"
#include "Number.h"

class CCoinPlay : public CGameObject
{
	vector<CNumber*> numbers;
	int coin;

public:
	CCoinPlay() { coin = 0; }
	CCoinPlay(vector<CNumber*> num) {
		coin = 0;
		for (int i = 0; i < num.size(); i++)
		{
			numbers.push_back(num[i]);
		}

	}
	void SetPositionNumbers(float x, float y);
	void AddCoin() { coin += 1; }

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

