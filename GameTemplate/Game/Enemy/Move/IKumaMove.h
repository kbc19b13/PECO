#pragma once

class IAcotr;
class Kuma;
class MoveEscape;

/// <summary>
/// �N�}�̈ړ������̊��N���X
/// ��{�ƂȂ�ϐ��A�֐�������
/// �ړ������N���X�͂��̃N���X���p�����āA�쐬���Ă���
/// </summary>
class IKumaMove : public IActor
{
public:
	IKumaMove(Kuma* kuma) :
		m_kuma(kuma)
	{

	}
	/// <summary>
	/// �ړ������B
	/// </summary>
	virtual void Move() = 0;
	
protected:
	Kuma* m_kuma = nullptr;	//���̃N���X�ňړ������Ă���N�}�B
	CVector3 m_initPos = CVector3::Zero();		//�N�}�̏������W�B
};

