#pragma once
#include "Enemy/Move/IKumaMove.h"

#include "Player.h"

/// <summary>
/// �N�}�̓����鏈��
/// </summary>

class MoveEscape : public IKumaMove
{
public:
	MoveEscape(Kuma* kuma);
	

	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move()override;

private:
	Player* m_player = nullptr;

};