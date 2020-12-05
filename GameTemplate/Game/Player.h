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
	

	/////////Singleton�p�^�[��///////////////
	//Player����̂Ɍ���
	static Player* P_GetInstance()
	{
		return m_instance;
	}

private:
	
	CharacterController m_CCon;

	
	CVector3 m_speed = { 0.0f, 0.0f, 0.0f };

	//AnimationClip�z���Animation�̕ϐ���ǉ�����
	//�A�j���[�V����
	Animation m_PlayerAnimation;
	AnimationClip m_PlayerAnimationClips[4];

	AnimationPlayController m_animPlayCon;

	
	
private:
	//�V���O���g���p�|�C���^
	static Player* m_instance;
};

