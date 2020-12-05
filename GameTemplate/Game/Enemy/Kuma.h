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

	void Update();

	/// <summary>
	/// �N�}�����O�̏��������s��
	/// </summary>
	/// <returns></returns>
	bool Start();

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
	/// <summary>
	/// �N�}�̍��W�Ɏw�肳�ꂽ�x�N�g���𑫂��Z����B
	/// </summary>
	/// <param name="move">�����Z����x�N�g��</param>
	void AddPosition(const CVector3& add)
	{
		m_pos += add;
	}
public:
	
	
	bool IsLive() const
	{
		return m_isLive;
	}
	bool IsDying() const
	{
		return m_isCotton;
	}
private:
	/// <summary>
	/// �X�e�[�g�}�V�������s
	/// </summary>
	void ExecuteFSM();
	/// <summary>
	/// �ʏ��Ԃ̎��̏��������s�B
	/// </summary>
	void ExecuteFSM_Normal();
	/// <summary>
	/// ������Ԃ̎��̏��������s�B
	/// </summary>
	void ExecuteFSM_Escape();
protected:

	enum State {
		State_Normal,			//�ʏ���
		State_TransitionEscape,	//�����ɐ؂�ւ����̏��
		State_Escape,			//�������
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

	Player* m_player = nullptr;
};

