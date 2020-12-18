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
	CVector3 ReturnPos = m_kuma->GetPos();
	CVector3 savePos = m_kuma->GetSavePos();
	CVector3 ReturnVector = savePos - ReturnPos;
	ReturnVector.Normalize();

	m_kuma->AddPosition(ReturnVector);
	//帰宅状態の処理
	if (savePos.x - ReturnPos.x <= 1.0f &&
		savePos.y - ReturnPos.y <= 1.0f &&
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