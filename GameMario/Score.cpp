#include "Score.h"
#include "Utils.h"
#include "Game.h"

CScore::CScore()
{

}



void CScore::SetPositionNumbers(float x, float y)
{
	numbers[0]->SetPosition(x, y);
	numbers[1]->SetPosition(x + 8, y);
	numbers[2]->SetPosition(x + 16, y);
	numbers[3]->SetPosition(x + 24, y);
	numbers[4]->SetPosition(x + 32, y);
	numbers[5]->SetPosition(x + 40, y);
	numbers[6]->SetPosition(x + 48, y);
}

void CScore::Render()
{

}

void CScore::PushNumbers(CNumber* num)
{

	numbers.push_back(num);
}

void CScore::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	int num = game->GetScore();
	int temp;


	for (int i = numbers.size() - 1; i >= 0; i--)
	{

		temp = num % 10;
		num = num / 10;
		numbers[i]->SetState(temp);
	}
}