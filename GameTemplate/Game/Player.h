#pragma once

#include "character/CharacterController.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/animation/AnimationPlayController.h"

class Player : public IActor
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	

	/////////Singletonパターン///////////////
	//Playerを一体に限定
	static Player* P_GetInstance()
	{
		return m_instance;
	}

private:
	
	CharacterController m_CCon;

	
	CVector3 m_speed = { 0.0f, 0.0f, 0.0f };

	//AnimationClip配列とAnimationの変数を追加する
	//アニメーション
	Animation m_PlayerAnimation;
	AnimationClip m_PlayerAnimationClips[4];

	AnimationPlayController m_animPlayCon;

	
	
private:
	//シングルトン用ポインタ
	static Player* m_instance;
};

