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
	//‹A‘îó‘Ô‚Ìˆ—
	CVector3 savePos = m_kuma->GetSavePos();
	
	//‹A‘îó‘Ô‚Ìˆ—
	if (savePos.x == m_pos.x &&
		savePos.y == m_pos.y &&
		savePos.z == m_pos.z)
	{
		m_kuma->SetisSavePos(true);
	}
	else {
		m_kuma->SetisSavePos(false);
	}

	//‰ŠúÀ•W‚É‚¢‚é‚©”»’è‚·‚é
	if (m_kuma->IsSavePos()) {
		m_kuma->ExecuteFSM_Normal();
	}
}