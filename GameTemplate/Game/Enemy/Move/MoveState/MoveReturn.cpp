#include "stdafx.h"
#include "MoveReturn.h"
#include "Enemy/Kuma.h"

MoveReturn::MoveReturn(Kuma* kuma) :
	IKumaMove(kuma)
{
	m_player = Player::P_GetInstance();
}
MoveReturn::~MoveReturn()
{

}

void MoveReturn::Move()
{
	//Playerとクマとの距離を求めて処理を行う
	//Playerの座標を取得する処理が入るので
	if (GetDistance(m_player->GetPosition(), m_kuma->GetPos()) < 100.0f)
	{
		//距離が100以下なら逃げ状態に遷移する。
		//移動処理を逃げる処理に切り替える。
		m_kuma->ExecuteFSM_Discovery();
	}

	CVector3 ReturnPos = CVector3::Zero();

	
	//帰宅状態の処理
	if (ReturnPos.x <= 1.0f &&
		ReturnPos.z <= 1.0f &&
		ReturnPos.x <= -1.0f &&
		ReturnPos.z <= -1.0f)
	{
		m_kuma->SetisSavePos(true);	
	}
	else {
		m_kuma->SetisSavePos(false);
	}

	//初期座標にいるか判定する
	if (m_kuma->IsSavePos()) {
		
		m_kuma->ExecuteFSM_Normal();
	}
	else
	{
		//帰宅状態の処理
		ReturnPos = m_kuma->GetPos();
		CVector3 savePos = m_kuma->GetSavePos();
		CVector3 ReturnVector = savePos - ReturnPos;
		ReturnVector.Normalize();

		m_kuma->SetMoveSpeed(ReturnVector);
	}
}