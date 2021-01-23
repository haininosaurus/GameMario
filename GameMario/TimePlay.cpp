#include "TimePlay.h"
#include "Utils.h"

CTime::CTime()
{
	time = TIME_LIMIT;
	time_start = (DWORD)GetTickCount64();
}

void CTime::PushNumbers(CNumber* num)
{
	numbers.push_back(num);
}

void CTime::SetPositionNumbers(float x, float y)
{
	numbers[0]->SetPosition(x, y);
	numbers[1]->SetPosition(x + 8, y);
	numbers[2]->SetPosition(x + 16, y);
}

void CTime::Render()
{
	int num = time;
	int temp;

	for (int i = numbers.size() - 1; i >= 0; i--)
	{

		temp = num % 10;
		//DebugOut(L"temp: %d\n", temp);
		num = num / 10;
		numbers[i]->SetState(temp);
	}
}

void CTime::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - time_start > 1000)
	{
		time -= 1;
		time_start = (DWORD)GetTickCount64();
	}
}