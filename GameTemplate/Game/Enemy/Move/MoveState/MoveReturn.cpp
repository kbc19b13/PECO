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
	
}