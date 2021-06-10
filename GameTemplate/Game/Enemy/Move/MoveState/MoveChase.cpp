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
	//Player�ƃN�}�Ƃ̋��������߂ď������s��
	//Player�̍��W���擾���鏈��������̂Œ���
	CVector3 direction = GetDirection(m_player->GetPosition(), m_kuma->GetPos());
	direction * 5;
	m_kuma->SetMoveSpeed(direction);

}