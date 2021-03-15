#pragma once

#include "Enemy/Move/IKumaMove.h"
#include "Player.h"

/// <summary>
/// �N�}�̈ړ�����(�㉺�ړ�)
/// </summary>
class KumaMoveUpDown : public IKumaMove
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="kuma">���̃N���X�ňړ�������N�}</param>
	KumaMoveUpDown(Kuma* kuma);
	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move() override;

private:
	Player* m_player = nullptr;
};

