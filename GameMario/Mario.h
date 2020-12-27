#pragma once
#include "GameObject.h"
#include "Collision.h"


#define MARIO_WALKING_SPEED								0.1f 
#define MARIO_RUNNING_SPEED								0.15f
#define MARIO_RUNNING_FAST_SPEED						0.2f

#define MARIO_JUMP_SPEED_Y								0.15f
#define MARIO_FLYING_SPEED_Y							0.03f
#define MARIO_JUMP_DEFLECT_SPEED						0.2f
#define MARIO_GRAVITY									0.001f
#define MARIO_DIE_DEFLECT_SPEED							0.5f

#define MARIO_STATE_IDLE								0
#define MARIO_STATE_WALKING_RIGHT						100
#define MARIO_STATE_WALKING_LEFT						110
#define MARIO_STATE_JUMP								200
#define MARIO_STATE_DIE									300
#define MARIO_STATE_RUNNING_RIGHT						400
#define MARIO_STATE_RUNNING_LEFT						410
#define MARIO_STATE_JUMP_RIGHT							210
#define MARIO_STATE_JUMP_LEFT							220
#define MARIO_STATE_KICK								500
#define MARIO_STATE_TAKE_TORTOISESHELL_RIGHT			600
#define MARIO_STATE_TAKE_TORTOISESHELL_LEFT				610
#define MARIO_STATE_TURN_LEFT							700
#define MARIO_STATE_TURN_RIGHT							710
#define MARIO_STATE_FIGHT								800
#define MARIO_STATE_RUNNING_RIGHT_FAST					420
#define MARIO_STATE_RUNNING_LEFT_FAST					430
#define MARIO_STATE_FLYING_LOW_RIGHT					900
#define MARIO_STATE_FLYING_LOW_LEFT						910
#define MARIO_STATE_FLYING_HIGH_RIGHT					920
#define MARIO_STATE_FLYING_HIGH_LEFT					930
#define MARIO_STATE_SIT									940
#define MARIO_STATE_SHOOT_FIRE_BULLET_RIGHT				950
#define MARIO_STATE_SHOOT_FIRE_BULLET_LEFT				960
#define MARIO_STATE_DEFLECT								970
#define MARIO_STATE_HEADUP								980
#define MARIO_STATE_SMOKE								990
#define MARIO_STATE_GROWUP								1000



#define MARIO_ANI_SMALL_IDLE_RIGHT						0
#define MARIO_ANI_SMALL_IDLE_LEFT						1
#define MARIO_ANI_BIG_IDLE_RIGHT						2
#define MARIO_ANI_BIG_IDLE_LEFT							3
#define MARIO_ANI_TAIL_IDLE_RIGHT						8
#define MARIO_ANI_TAIL_IDLE_LEFT						9
#define MARIO_ANI_FIRE_IDLE_RIGHT						12
#define MARIO_ANI_FIRE_IDLE_LEFT						13

#define MARIO_ANI_SMALL_WALKING_RIGHT					4
#define MARIO_ANI_SMALL_WALKING_LEFT					5
#define MARIO_ANI_BIG_WALKING_RIGHT						6
#define MARIO_ANI_BIG_WALKING_LEFT						7
#define MARIO_ANI_TAIL_WALKING_RIGHT					10
#define MARIO_ANI_TAIL_WALKING_LEFT						11
#define MARIO_ANI_FIRE_WALKING_RIGHT					14
#define MARIO_ANI_FIRE_WALKING_LEFT						15

#define MARIO_ANI_SMALL_RUNNING_RIGHT					16
#define MARIO_ANI_SMALL_RUNNING_LEFT					17
#define MARIO_ANI_BIG_RUNNING_RIGHT						18
#define MARIO_ANI_BIG_RUNNING_LEFT						19
#define MARIO_ANI_TAIL_RUNNING_RIGHT					20
#define MARIO_ANI_TAIL_RUNNING_LEFT						21
#define MARIO_ANI_FIRE_RUNNING_RIGHT					22
#define MARIO_ANI_FIRE_RUNNING_LEFT						23

#define MARIO_ANI_SMALL_JUMPING_RIGHT					24
#define MARIO_ANI_SMALL_JUMPING_LEFT					25
#define MARIO_ANI_BIG_JUMPING_RIGHT						26
#define MARIO_ANI_BIG_JUMPING_LEFT						27
#define MARIO_ANI_TAIL_JUMPING_RIGHT					28
#define MARIO_ANI_TAIL_JUMPING_LEFT						29
#define MARIO_ANI_FIRE_JUMPING_RIGHT					30
#define MARIO_ANI_FIRE_JUMPING_LEFT						31

#define MARIO_ANI_SMALL_KICK_RIGHT						32
#define MARIO_ANI_SMALL_KICK_LEFT						33
#define MARIO_ANI_BIG_KICK_RIGHT						34
#define MARIO_ANI_BIG_KICK_LEFT							35
#define MARIO_ANI_TAIL_KICK_RIGHT						36
#define MARIO_ANI_TAIL_KICK_LEFT						37
#define MARIO_ANI_FIRE_KICK_RIGHT						38
#define MARIO_ANI_FIRE_KICK_LEFT						39

#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_RIGHT	40
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_LEFT	41
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_RIGHT		42
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_LEFT			43
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_JUMP_RIGHT	44
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_JUMP_LEFT	45

#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_IDLE_RIGHT		46
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_IDLE_LEFT		47
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_RIGHT			48
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_LEFT			49
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_JUMP_RIGHT		50
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_JUMP_LEFT		51

#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_RIGHT	52
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_LEFT		53
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_RIGHT			54
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_LEFT			55
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_JUMP_RIGHT	56
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_JUMP_LEFT		57

#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_IDLE_RIGHT	58
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_IDLE_LEFT		59
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_RIGHT			60
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_LEFT			61
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_JUMP_RIGHT	62
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_JUMP_LEFT		63

#define MARIO_ANI_SMALL_TURN_LEFT						64
#define MARIO_ANI_SMALL_TURN_RIGHT						65
#define MARIO_ANI_BIG_TURN_LEFT							66
#define MARIO_ANI_BIG_TURN_RIGHT						67
#define MARIO_ANI_TAIL_TURN_LEFT						68
#define MARIO_ANI_TAIL_TURN_RIGHT						69
#define MARIO_ANI_FIRE_TURN_LEFT						70
#define MARIO_ANI_FIRE_TURN_RIGHT						71

#define MARIO_ANI_TAIL_FIGHT							72

#define MARIO_ANI_SMALL_RUNNING_RIGHT_FAST				73
#define MARIO_ANI_SMALL_RUNNING_LEFT_FAST				74
#define MARIO_ANI_BIG_RUNNING_RIGHT_FAST				75
#define MARIO_ANI_BIG_RUNNING_LEFT_FAST					76
#define MARIO_ANI_TAIL_RUNNING_RIGHT_FAST				77
#define MARIO_ANI_TAIL_RUNNING_LEFT_FAST				78
#define MARIO_ANI_FIRE_RUNNING_RIGHT_FAST				79
#define MARIO_ANI_FIRE_RUNNING_LEFT_FAST				80

#define MARIO_ANI_FLY_LOW_RIGHT							81
#define MARIO_ANI_FLY_LOW_LEFT							82

#define MARIO_ANI_FLY_HIGH_RIGHT						83
#define MARIO_ANI_FLY_HIGH_LEFT							84

#define MARIO_ANI_BIG_SIT_RIGHT							85
#define MARIO_ANI_BIG_SIT_LEFT							86
#define MARIO_ANI_TAIL_SIT_RIGHT						87
#define MARIO_ANI_TAIL_SIT_LEFT							88
#define MARIO_ANI_FIRE_SIT_RIGHT						89
#define MARIO_ANI_FIRE_SIT_LEFT							90

#define MARIO_ANI_SHOOT_FIRE_BULLET_RIGHT				91
#define MARIO_ANI_SHOOT_FIRE_BULLET_LEFT				92

#define MARIO_ANI_DEFLECT								93
#define MARIO_ANI_HEADUP								94

#define MARIO_ANI_SMOKE									95
#define MARIO_ANI_GROWUP_RIGHT							96
#define MARIO_ANI_GROWUP_LEFT							97

#define MARIO_ANI_DIE									98

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL	3
#define MARIO_LEVEL_FIRE	 4

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 27
#define MARIO_BIG_SIT_BBOX_WIDTH	14
#define MARIO_BIG_SIT_BBOX_HEIGHT	18

#define MARIO_TAIL_BBOX_WIDTH 21
#define MARIO_TAIL_BBOX_HEIGHT 28
#define MARIO_TAIL_SIT_BBOX_WIDTH	22
#define MARIO_TAIL_SIT_BBOX_HEIGHT	18

#define MARIO_FIRE_BBOX_WIDTH 14
#define MARIO_FIRE_BBOX_HEIGHT 27
#define MARIO_FIRE_SIT_BBOX_WIDTH	14
#define MARIO_FIRE_SIT_BBOX_HEIGHT	18

#define MARIO_SMALL_BBOX_WIDTH  12
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_SLIDE_WALKING_TIME 300



class CMario : public CollisionObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	bool is_high;
	int intro_state;
	int run_state;
	int run_fast_state;
	int jump_state;
	int kick_state;
	int turn_state;
	int fight_state;
	int fall_state;
	int fly_low_state;
	int fly_high_state;
	int deflect_state;
	int headup_state;
	int sit_state;
	int slide_state;

	int smoke_state;
	int growup_state;

	DWORD smoke_start;
	DWORD growup_start;
	int shoot_fire_bullet_state;

	int checkSit;
	
	float walking_right_speech;
	float walking_left_speech;

	int take_tortoistate_state;

	CGameObject* tortoiseshell;
	CGameObject* fire_bullet[2];
	DWORD jump_start;
	DWORD kick_start;
	DWORD shoot_fire_bullet_start;
	DWORD fight_start;
	DWORD fly_low_start;
	DWORD fly_high_start;
	DWORD running_time_right;
	DWORD running_time_left;
	DWORD walking_time_right;
	DWORD walking_time_left;

	DWORD sliding_time_right;
	DWORD sliding_time_left;
	DWORD create_time;

	float speech_Jump;

public:

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }

	int GetLevel() { return level; }
	int GetJumpState() { return jump_state; }
	int GetStateTakeTortoiseshell() { return take_tortoistate_state; }
	int GetKickState() { return kick_state; }
	int GetFightState() { return fight_state; }
	int GetRunState() { return run_state; }
	int GetFlyLowState() { return fly_low_state; }
	int GetFlyHighState() { return fly_high_state; }
	int GetSitState() { return sit_state; }
	int GetShootFireBulletState() { return shoot_fire_bullet_state; }
	int GetSlideState(){return slide_state;}
	int GetSmokeState() { return smoke_state; }
	int GetGrowupState() { return growup_state; }
	int GetDeflectState() { return deflect_state; }
	int GetFallState() { return fall_state; }
	float GetWalkingRightSpeech() { return walking_right_speech; }
	float GetWalkingLeftSpeech() { return walking_left_speech; }
	bool GetIsHigh() { return is_high; }
	float GetSpeechJump() { return speech_Jump; }
	DWORD GetWalkRightTime() { return walking_time_right; }
	DWORD GetWalkLeftTime() { return walking_time_left; }
	DWORD GetRunningRightTime() { return running_time_right; }
	DWORD GetRunningLeftTime() { return running_time_left; }
	DWORD GetJumpStart() { return jump_start; }
	DWORD GetKickStart() { return kick_start; }
	DWORD GetFightStart() { return fight_start; }
	DWORD GetFlyLowStart() { return fly_low_start; }
	DWORD GetFlyHighStart() { return fly_high_start; }
	DWORD GetShootFireBulletStart() { return shoot_fire_bullet_start; }

	void StartUntouchable() { untouchable = 1; untouchable_start = (DWORD)GetTickCount64(); }

	void SetIntroState(int s) { intro_state = s; }
	void SetJumpStart(DWORD t){ jump_start = t; }
	void SetKickStart(int t) { kick_start = t; }
	void SetJumpState(int j) { jump_state = j; }
	void SetFightState(int f) { fight_state = f; }
	void SetSitState(int s) { sit_state = s; }
	void SetDeflectState(int d) { deflect_state = d; }

	void SetShootFireBulletState(int s) { shoot_fire_bullet_state = s; }
	void SetWalkRightTime(DWORD t) { walking_time_right = t; }
	void SetWalkLeftTime(DWORD t) { walking_time_left = t; }
	void SetRunningRightTime(DWORD t) { running_time_right = t; }
	void SetRunningLeftTime(DWORD t) { running_time_left = t; }
	void SetWalkingRightSpeech() {walking_right_speech += 0.005f;}
	void ResetWalkingRightSpeech() { walking_right_speech = 0; }
	void ResetWalkingLeftSpeech() { walking_left_speech = 0; }
	void SetWalkingLeftSpeech() { walking_left_speech += 0.005f;}
	void SetSlidingTimeRight() { sliding_time_right += 20; }
	void SetSlidingTimeLeft() { sliding_time_left += 20; }
	DWORD GetSlidingTimeRight() { return sliding_time_right; }
	DWORD GetSlidingTimeLeft() { return sliding_time_left; }
	void ResetSlidingTimeRight() { sliding_time_right = 0; }
	void ResetSlidingTimeLeft() { sliding_time_left = 0; }

	void SetShootFireBulletStart(DWORD t) { shoot_fire_bullet_start = t; }
	void SetSpeechJump() { speech_Jump += 0.0025f; }
	void SetFightStart(DWORD t) { fight_start = t; }
	void SetFlyLowStart(DWORD t) { fly_low_start = t; }
	void SetFlyHighStart(DWORD t) { fly_high_start = t; }
	void SetSmokeStart(DWORD t) { smoke_start = t; }

	void CreateFireBullet(CGameObject* fireBullet);
	void ShootFireBullet();

	void CreateIntroAnimationMario();

	int GetCurrentWidthMario();
	int GetCurrentHeightMario();
	double GetCenterWidthMario();
	double GetCenterHeightMario();


	void Reset();

	virtual void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};