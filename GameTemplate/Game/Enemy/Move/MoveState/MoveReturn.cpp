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
	CVector3 ReturnPos = m_kuma->GetPos();
	CVector3 savePos = m_kuma->GetSavePos();
	CVector3 ReturnVector = savePos - ReturnPos;
	ReturnVector.Normalize();

	m_kuma->AddPosition(ReturnVector);
	//‹A‘îó‘Ô‚Ìˆ—
	if (savePos.x - ReturnPos.x <= 1.0f &&
		savePos.y - ReturnPos.y <= 1.0f &&
		savePos.z - ReturnPos.z <= 1.0f)
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