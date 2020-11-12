#pragma once

#include "Move/IKumaMove.h"

/// <summary>
/// �X�̃N�}
/// </summary>
class Kuma final : public IActor
{  
public:
	
	Kuma()
	{}

	virtual ~Kuma()
	{}

	void Update();

	bool Start();

	void Draw();
	/// <summary>
	/// �㉺�ړ��̏������쐬�B
	/// </summary>
	void CreateMoveUpDown();

	void CreateMoveLR();

	void CreateMoveTrun();
public:
	
	
	bool IsLive() const
	{
		return m_isLive;
	}
	bool IsDying() const
	{
		return m_isCotton;
	}

protected:

	enum State {
		State_Normal,
		State_Dying,
		State_Death
	};
	State m_state = State_Normal;  //�X�e�[�g


	//AnimationClip�z���Animation�̕ϐ���ǉ�����
	//�A�j���[�V����
	Animation m_MoriAnimation;
	AnimationClip m_MoriAnimationClips[5];

	bool m_isLive = true;				//�����Ă�H
	bool m_isCotton = true;				//�ȓ����Ă�H
	std::unique_ptr< IKumaMove >	m_move;	//�N�}�̈ړ������B
};

