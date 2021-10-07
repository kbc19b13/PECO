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
	//Playerとクマとの方向を求めて処理を行う
	//Playerの座標を取得する処理が入るので注意
	CVector3 direction = GetDirection(m_player->GetPosition(), m_kuma->GetPos());
	direction = direction * 2;
	m_kuma->SetMoveSpeed(direction);

}