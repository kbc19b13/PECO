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

	/// <summary>
	/// �J�n����
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �����擾����
	/// </summary>
	void Direction();
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �A�j���[�V�����Đ�
	/// </summary>
	void Anim();
	/// <summary>
	/// �A�j���[�V�����̏�����
	/// </summary>
	void AnimInit();

private:
	////////////////*�\���̕ϐ�*/////////////////////
	//�t���[�g�Ή����Ԍv���ϐ�
	float frametime = 0.0f;
	
	//�L�����R��
	CharacterController m_CCon;

	//AnimationClip�z���Animation�̕ϐ���ǉ�����
	//�A�j���[�V����
	Animation m_PlayerAnimation;
	AnimationClip m_PlayerAnimationClips[1];

	//AnimationPlayController m_animPlayCon;
	
	//////////////////////////////////////////////////
	
	////////////////*�����擾�̕ϐ�*//////////////////
	//player�̑O�����擾
	CVector3 p_mae = CVector3::Front();
	//player�̏�����擾
	CVector3 p_ue = CVector3::Up();
	//player�̉E�����擾
	CVector3 p_migi = CVector3::Right();

	//Quaternion���s��ɕϊ�
	CMatrix p_rot = CMatrix::Identity();
	//////////////////////////////////////////////////
	
	float lStickY = 0.0f;	//L�X�e�B�b�N��Y�����
	float lStickX = 0.0f;	//L�X�e�B�b�N��X�����

public:
	/////////Singleton�p�^�[��///////////////
	//Player����̂Ɍ���
	static Player* P_GetInstance()
	{
		return m_instance;
	}
private:
	//�V���O���g���p�|�C���^
	static Player* m_instance;
};

