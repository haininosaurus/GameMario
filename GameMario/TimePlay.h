#pragma once
#include "GameObject.h"
#include "Number.h"

#define TIME_LIMIT			300

class CTime : public CGameObject
{
	vector<CNumber*> numbers;
	int time;
	DWORD time_start;

public:
	CTime();
	CTime(vector<CNumber*> num) {
		time = TIME_LIMIT;
		time_start = (DWORD)GetTickCount64();

		for (int i = 0; i < num.size(); i++)
			numbers.push_back(num[i]);
	}
	void PushNumbers(CNumber* num);
	void SetPositionNumbers(float x, float y);

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

