#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// �N�}�̓����鏈��
/// </summary>

class MoveNormal : public IKumaMove
{
public:
	MoveNormal(Kuma* kuma);
	~MoveNormal();

	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move()override;

private:
	Player* m_player = nullptr;

};