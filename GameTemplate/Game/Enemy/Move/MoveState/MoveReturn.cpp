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
	if (GetDistance(m_player->GetPosition(), m_pos) < 100.0f)
	{
		//距離が100以下なら逃げ状態に遷移する。
		//移動処理を逃げる処理に切り替える。
		m_kuma->ExecuteFSM_Discovery();
	}

	//帰宅状態の処理
	CVector3 ReturnPos = m_kuma->GetPos();
	CVector3 savePos = m_kuma->GetSavePos();
	CVector3 ReturnVector = savePos - ReturnPos;
	ReturnVector.Normalize();

	m_kuma->AddPosition(ReturnVector);
	//帰宅状態の処理
	if (savePos.x - ReturnPos.x <= 1.0f &&
		savePos.z - ReturnPos.z <= 1.0f)
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
}