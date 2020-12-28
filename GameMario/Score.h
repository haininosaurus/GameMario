#pragma once
#include "GameObject.h"
#include "Number.h"
#include "Utils.h"

class CScore : public CGameObject
{
	vector<CNumber*> numbers;
	int score;

public:
	CScore();
	CScore(vector<CNumber*> num) {
		score = 0;
		for (int i = 0; i < num.size(); i++)
		{
			numbers.push_back(num[i]);
		}

	}
	void PushNumbers(CNumber* num);
	void SetPositionNumbers(float x, float y);
	void SetScore(int s) { score += s; }

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

