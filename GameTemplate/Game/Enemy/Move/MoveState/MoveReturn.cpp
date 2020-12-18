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
	//�A���Ԃ̏���
	CVector3 savePos = m_kuma->GetSavePos();
	
	//�A���Ԃ̏���
	if (savePos.x == m_pos.x &&
		savePos.y == m_pos.y &&
		savePos.z == m_pos.z)
	{
		m_kuma->SetisSavePos(true);
	}
	else {
		m_kuma->SetisSavePos(false);
	}

	//�������W�ɂ��邩���肷��
	if (m_kuma->IsSavePos()) {
		m_kuma->ExecuteFSM_Normal();
	}
}