#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// �N�}�̓����鏈��
/// </summary>

class MoveDiscovery : public IKumaMove
{
public:
	MoveDiscovery(Kuma* kuma);
	

	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move()override;

private:
	



	//�N���X�̃��[�h
private:
	Player* m_player = nullptr;

};