#pragma once

#include "Move/IKumaMove.h"
class Player;

/// <summary>
/// �X�̃N�}
/// �G�N�}�̏�������
/// </summary>
class Kuma final : public IActor
{  
	//�\���̂͏�ʂɕ`�����֐��Ɏg�p����Ƃ��ɃG���[���o��c
protected:
	//�����ړ��X�e�[�g�\����
	enum MoveState {
		State_Circle,			//�~�ړ�
		State_LR,				//���E�ړ�
		State_UpDown,			//�㉺�ړ�
	};
	//������
	enum DiscoverySituation
	{
		States_Still,			//����
		States_Found,			//��������
		States_Discovered		//�������ꂽ
	};
	//��ԊǗ��\����
	enum State {
		State_Normal,			//�ʏ���
		State_Discovery,		//�������
		State_Chase,			//�ǐՏ��
		State_Escape,			//�������
		State_Return,			//�A����
		State_Restraint,		//�S�����
		State_Fainted,			//�C����
		State_Death				//���S���
	};
	//�X�e�[�g�؂�ւ����N�G�X�g
	struct ChangeStateRequest {
		State nextState;	//���̃X�e�[�g
		bool isRequest;		//���N�G�X�g���󂯂Ă���H

	};

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
	/// <summary>
	/// ���ʏ���
	/// </summary>
	void CommonUpdate();
	/// <summary>
	/// ���ʈړ�����
	/// </summary>
	void CommonMove();
	/// <summary>
	/// �O�Ɍ���
	/// </summary>
	void Forward(const CVector3 speed);
	/// <summary>
	/// ����p�̔�����s��
	/// </summary>
	void OutLook();
private://�X�e�[�g�̊Ǘ��֐�
	/// <summary>
	/// �X�e�[�g�}�V�������s
	/// </summary>
	void ExecuteFSM();

public:/*�����ړ���Ԃ��쐬����֐�*/
	
	/// /// <summary>
	/// �㉺�ړ��̏������쐬�B
	/// </summary>
	void CreateMoveUpDown();
	/// <summary>
	/// ���E�ړ��̏������쐬
	/// </summary>
	void CreateMoveLR();
	/// <summary>
	/// �~�ړ��̏������쐬
	/// </summary>
	void CreateMoveCircle();
public:/*��Ԃ��쐬����֐�*/
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
	/// <summary>
	/// �ǐՏ�Ԃ̎��̏������쐬
	/// </summary>
	void ExecuteFSM_Chase();
	
	
public:/*�擾�֐�*/
	/// <summary>
	/// �N�}�̍��W���擾
	/// </summary>
	const CVector3& GetPos() const
	{
		return m_pos;
	}
	/// <summary>
	/// �������W���擾�B
	/// </summary>
	/// <returns></returns>
	const CVector3& GetSavePos() const
	{
		return m_savePos;
	}
	/// <summary>
/// ���݂̏�Ԃ��擾
/// </summary>
/// <returns></returns>
	const MoveState GetState() const
	{
		return m_movestate;
	}
public:/*�ݒ�֐�*/
	/// <summary>
	/// �A�j���[�V�����̏�Ԃ�ݒ�
	/// </summary>
	void SetAnimation(const int number)
	{
		m_MoriAnimation.Play(number);
	}
	/// <summary>
	/// �������W��ݒ肷��
	/// </summary>
	void SetSavePos(const CVector3 pos)
	{
		m_savePos = pos;
	}
	/// <summary>
	/// �������W���̔��茋�ʂ�ݒ�
	/// </summary>
	/// <param name="issavepos">�ݒ肷�锻�茋��</param>
	void SetisSavePos(const bool issavepos)
	{
		m_isSavePos = issavepos;
	}
	/// <summary>
	/// ������Ԃ̏󋵂�ݒ�
	/// </summary>
	/// <returns>�ݒ肷���</returns>
	void SetStates(const DiscoverySituation states)
	{
		m_states = states;
	}
	/// <summary>
	/// ������Ԃ̏󋵂��擾
	/// </summary>
	/// <returns>��</returns>
	const DiscoverySituation GetStates() const
	{
		return m_states;
	}
	/// <summary>
	/// �t���[�����Ԃ��擾
	/// </summary>
	/// <returns></returns>
	const float GetFrameTime() const
	{
		return m_frametime;
	}
	/// <summary>
	/// �t���[�����Ԃ�ݒ�
	/// </summary>
	/// <param name="frametime"></param>
	void SetFrameTime(const float frametime)
	{
		m_frametime = frametime;
	}
	/// <summary>
	/// ���݂̏�Ԃ�ݒ�
	/// </summary>
	MoveState SetState(const MoveState state) {
		m_movestate = state;
	}
public:/*����֐�*/
	/// <summary>
	/// �������W����
	/// </summary>
	/// <returns></returns>
	bool IsSavePos() const
	{
		return m_isSavePos;
	}
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns></returns>
	bool IsLive() const
	{
		return m_isLive;
	}
	/// <summary>
	/// ���S����
	/// </summary>
	/// <returns></returns>
	bool IsDying() const
	{
		return m_isCotton;
	}

public://���Z�֐�
	/// <summary>
	/// 1�t���[���̎��Ԃ����Z
	/// </summary>
	/// <param name="addtime"></param>
	void AddTime(const float addtime)
	{
		m_frametime += addtime;
	}

protected:
	ChangeStateRequest m_changeStateRequest;
	MoveState m_movestate = State_LR;			//�ړ����

	State m_state = State_Normal;				//�X�e�[�g

	DiscoverySituation m_states = States_Still;	//��

	//AnimationClip�z���Animation�̕ϐ���ǉ�����
	//�A�j���[�V����
	Animation m_MoriAnimation;
	AnimationClip m_MoriAnimationClips[7];

	bool m_isLive = true;					//�����Ă�H
	bool m_isCotton = true;					//�ȓ����Ă�H
	CVector3 m_savePos = CVector3::Zero();	//�������W
	bool m_isSavePos = true;				//�������W���𔻒�
	float m_frametime = 0.0f;				//�ҋ@���Ԃ��v���B

protected:

	std::unique_ptr< IKumaMove >	m_kumamove;	//�N�}�̈ړ������B

	Player* m_player = nullptr;
};

