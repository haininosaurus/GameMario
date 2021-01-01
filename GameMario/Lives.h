#pragma once
#include "GameObject.h"
#include "Number.h"

class CLives : public CGameObject
{
	vector<CNumber*> numbers;
	int lives;

public:
	CLives() { lives = 3; }
	CLives(vector<CNumber*> num) {
		lives = 3;
		for (int i = 0; i < num.size(); i++)
		{
			numbers.push_back(num[i]);
		}

	}
	void SetPositionNumbers(float x, float y);
	void AddLives() { lives += 1; }
	void MinusLives() { lives -= 1; }

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

