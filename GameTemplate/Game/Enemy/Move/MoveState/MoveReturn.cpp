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
	
}