#include "stdafx.h"
#include "MoveReturn.h"
#include "Enemy/Kuma.h"

MoveReturn::MoveReturn(Kuma* kuma) :
	IKumaMove(kuma)
{

}
MoveReturn::~MoveReturn()
{

}

void MoveReturn::Move()
{
	//帰宅状態の処理
	CVector3 savePos = m_kuma->GetSavePos();
	
	//帰宅状態の処理
	if (savePos.x == m_pos.x &&
		savePos.y == m_pos.y &&
		savePos.z == m_pos.z)
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