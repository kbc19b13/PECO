#pragma once

class Kuma;
class MoveEscape;

/// <summary>
/// �N�}�̈ړ������̊��N���X
/// </summary>
class IKumaMove
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

	//���ʏ���
	void KumaUpdate();

	void Escape();

	void ChaseDown();

protected:
	Kuma* m_kuma = nullptr;	//���̃N���X�ňړ������Ă���N�}�B
	CVector3 m_initPos;		//�N�}�̏������W�B

protected:
	//MoveEscape m_Escape;
};

