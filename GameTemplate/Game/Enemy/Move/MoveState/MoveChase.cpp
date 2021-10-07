#include "stdafx.h"
#include "MoveChase.h"
#include "Enemy/Kuma.h"

MoveChase::MoveChase(Kuma* kuma) :
	IKumaMove(kuma)
{
	m_player = Player::P_GetInstance();
}
MoveChase::~MoveChase()
{

}

void MoveChase::Move()
{
	//Player�ƃN�}�Ƃ̕��������߂ď������s��
	//Player�̍��W���擾���鏈��������̂Œ���
	CVector3 direction = GetDirection(m_player->GetPosition(), m_kuma->GetPos());
	direction = direction * 2;
	m_kuma->SetMoveSpeed(direction);

}