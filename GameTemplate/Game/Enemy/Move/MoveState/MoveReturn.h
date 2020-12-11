#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// �N�}�̓����鏈��
/// </summary>

class MoveReturn : public IKumaMove
{
public:
	MoveReturn(Kuma* kuma);
	~MoveReturn();

	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move()override;

private:
	Player* m_player = nullptr;

};