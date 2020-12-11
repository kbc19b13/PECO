#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// �N�}��������O�̑ҋ@��������
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
	float frametime = 0.0f;		//�ҋ@���ԗp�̌v���ϐ�

	//�N���X�̃��[�h
private:
	Player* m_player = nullptr;

};