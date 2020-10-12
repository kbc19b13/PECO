#pragma once
#include "../mtEngine/mtGameObject.h"
#include "character/CharacterController.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/animation/AnimationPlayController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Draw();

	const CVector3& GetPosition(){
		return m_pos;
	}

	void SetPosition(const CVector3 pos) {
		m_pos = pos;
	}

private:
	SkinModel m_model;									//スキンモデル。

	CharacterController m_CCon;

	CVector3 m_pos = { 2400.0f, 30.0f, -2400.0f };
	CVector3 m_speed = { 0.0f, 0.0f, 0.0f };

	//AnimationClip配列とAnimationの変数を追加する
	//アニメーション
	Animation m_PlayerAnimation;
	AnimationClip m_PlayerAnimationClips[4];

	AnimationPlayController m_animPlayCon;
};

