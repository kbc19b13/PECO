#pragma once

#include "Enemy/Move/IKumaMove.h"

/// <summary>
/// �N�}�̈ړ�����(�㉺�ړ�)
/// </summary>
class KumaMoveLR : public IKumaMove
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="kuma">���̃N���X�ňړ�������N�}</param>
	KumaMoveLR(Kuma* kuma);
	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move() override;
protected:
};

