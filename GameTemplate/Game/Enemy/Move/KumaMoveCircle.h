#pragma once

#include "Enemy/Move/IKumaMove.h"

/// <summary>
/// �N�}�ړ�����
/// </summary>

class KumaMoveCircle : public IKumaMove
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// /// <param name="kuma">���̃N���X�ňړ�������N�}</param>
	KumaMoveCircle(Kuma* kuma);
	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move() override;
protected:
	CVector3 m_Speed = CVector3::Zero();		// ���x
	float m_Radius = 0.0f;		// ���a(�`��p)
	float m_Angle = 0.0f;		// �����̊p�x
	
};

