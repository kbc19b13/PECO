#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// �N�}�̓����鏈��
/// </summary>

class MoveEscape : public IKumaMove
{
public:
	MoveEscape(Kuma* kuma);
	~MoveEscape();

	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move()override;

private:
	Player* m_player = nullptr;

};