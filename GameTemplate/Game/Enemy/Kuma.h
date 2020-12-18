#pragma once

#include "Move/IKumaMove.h"
class Player;

/// <summary>
/// �X�̃N�}
/// �G�N�}�̏�������
/// </summary>
class Kuma final : public IActor
{  
	
public:
	
	Kuma()
	{}

	virtual ~Kuma()
	{}
	/// <summary>
	/// �N�}�̍X�V�֐�
	/// �K�؂�Move���Ăяo���X�V����B
	/// </summary>
	void Update();
	/// <summary>
	/// �N�}�����O�̏��������s��
	/// </summary>
	/// �A�j���[�V�����̏�����
	/// <returns></returns>
	bool Start();

	//��Ԃ��쐬����֐�
public:
	/// <summary>
	/// �㉺�ړ��̏������쐬�B
	/// </summary>
	void CreateMoveUpDown();
	/// <summary>
	/// ���E�ړ��̏������쐬
	/// </summary>
	void CreateMoveLR();
	/// <summary>
	/// �~��]�̏������쐬
	/// </summary>
	void CreateMoveTrun();
public:
	/// �ʏ��Ԃ̎��̏������쐬�B
	/// </summary>
	void ExecuteFSM_Normal();
	/// <summary>
	/// ������Ԃ̎��̏������쐬�B
	/// </summary>
	void ExecuteFSM_Discovery();
	/// <summary>
	/// ������Ԃ̎��̏������쐬�B
	/// </summary>
	void ExecuteFSM_Escape();
	/// <summary>
	/// �A���Ԃ̎��̏������쐬�B
	/// </summary>
	void ExecuteFSM_Return();
	
public:
	/// <summary>
	/// �N�}�̍��W�Ɏw�肳�ꂽ�x�N�g���𑫂��Z����B
	/// </summary>
	/// <param name="move">�����Z����x�N�g��</param>
	void AddPosition(const CVector3& add)
	{
		m_pos += add;
	}
	/// <summary>
	/// Player�Ƃ̋����𔻒肷��֐�
	/// </summary>
	float PE_GetDistance();
	/// <summary>
	/// �A�j���[�V�����̏�Ԃ�ύX
	/// </summary>
	void SetAnimation(const int number)
	{
		m_MoriAnimation.Play(number);
	}
	/// <summary>
	/// �������W���擾�B
	/// </summary>
	/// <returns></returns>
	const CVector3& GetSavePos() const
	{
		return m_SavePos;
	}
	/// <summary>
	/// �������W���̔��茋�ʂ�ݒ�
	/// </summary>
	/// <param name="issavepos">�ݒ肷�锻�茋��</param>
	void SetisSavePos(const bool issavepos)
	{
		m_isSavePos = issavepos;
	}
	const float GetFrameTime() const
	{
		return m_frametime;
	}
	void SetFrameTime(const float frametime)
	{
		m_frametime = frametime;
	}
	void AddTime(const float addtime)
	{
		m_frametime += addtime;
	}

	//������Ԃ̐ݒ�
	void SetState();
public:
	bool IsSavePos() const
	{
		return m_isSavePos;
	}
	bool IsLive() const
	{
		return m_isLive;
	}
	bool IsDying() const
	{
		return m_isCotton;
	}

	//�X�e�[�g�̊Ǘ��֐�
private:
	/// <summary>
	/// �X�e�[�g�}�V�������s
	/// </summary>
	void ExecuteFSM();
	/// <summary>


	

protected:

	//�����ړ��X�e�[�g�\����
	enum MoveState {
		State_Circle,		//�~�ړ�
		State_LR,			//���E�ړ�
		State_UpDown		//�㉺�ړ�
	};
	
	//��ԊǗ��\����
	enum State {
		State_Normal,			//�ʏ���
		State_Discovery,		//�������
		State_Escape,			//�������
		State_Return,			//�A����
		State_Restraint,		//�S�����
		State_Fainted,			//�C����
		State_Death				//���S���
	};

	MoveState m_movestate = State_Circle;	//�ړ����

	State m_state = State_Normal;  //�X�e�[�g


	//AnimationClip�z���Animation�̕ϐ���ǉ�����
	//�A�j���[�V����
	Animation m_MoriAnimation;
	AnimationClip m_MoriAnimationClips[7];

	bool m_isLive = true;					//�����Ă�H
	bool m_isCotton = true;					//�ȓ����Ă�H
	CVector3 m_SavePos = CVector3::Zero();	//�������W
	bool m_isSavePos = true;				//�������W���𔻒�
	float m_frametime = 0.0f;	//�ҋ@���Ԃ��v���B

protected:

	std::unique_ptr< IKumaMove >	m_kumamove;	//�N�}�̈ړ������B

	Player* m_player = nullptr;
};

