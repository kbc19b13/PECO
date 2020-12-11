#pragma once
#include "Enemy/Move/IKumaMove.h"


/// <summary>
/// �X�e�[�g�p�^�[��
/// �X�e�[�g�Ǘ����s���N���X
/// </summary>
class IMoveState : public IKumaMove
{
public:
	/*
	�X�e�[�g�Ǘ����s���ۂɐ�ɃN���X�̃��[�h���s���Ă������߁A
	Start�֐��ADelete�֐����ĂԂ��Ƃ��ł��Ȃ��̂ŁA
	Start = Enter
	Delete = Leave
	�Ƃ��Ĉ����֐����쐬����B
	*/

	/// <summary>
	/// ����֐�(��Ԑ؂�ւ����̊֐�)
	/// </summary>
	virtual void Enter();		
	/// <summary>
	/// ����֐�(��Ԑ؂�ւ����̊֐�)
	/// </summary>
	virtual void Leave();		
};