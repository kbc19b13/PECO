#pragma once

class Kuma;
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
protected:
	Kuma* m_kuma = nullptr;	//���̃N���X�ňړ������Ă���N�}�B
};

