#include "QuestionBlock.h"

//CQuestionBlock::CQuestionBlock(float x, float y) :CGameObject(x, y) {}

void CQuestionBlock::Render() {
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	ani = CAnimations::GetInstance()->Get(502);

	ani->Render(x, y);
}

void CQuestionBlock::Update(DWORD dt) {

}