#pragma once
#include "Enemy/Move/IKumaMove.h"

#include "Player.h"

/// <summary>
/// �N�}�̓����鏈��
/// </summary>

class MoveChase : public IKumaMove
{
public:
	MoveChase(Kuma* kuma);
	~MoveChase();

	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move()override;

private:
	Player* m_player = nullptr;

};