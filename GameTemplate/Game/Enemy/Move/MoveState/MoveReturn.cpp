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
	//Player�ƃN�}�Ƃ̋��������߂ď������s��
	//Player�̍��W���擾���鏈��������̂�
	if (GetDistance(m_player->GetPosition(), m_pos) < 100.0f)
	{
		//������100�ȉ��Ȃ瓦����ԂɑJ�ڂ���B
		//�ړ������𓦂��鏈���ɐ؂�ւ���B
		m_kuma->ExecuteFSM_Discovery();
	}

	//�A���Ԃ̏���
	CVector3 ReturnPos = m_kuma->GetPos();
	CVector3 savePos = m_kuma->GetSavePos();
	CVector3 ReturnVector = savePos - ReturnPos;
	ReturnVector.Normalize();

	m_kuma->AddPosition(ReturnVector);
	//�A���Ԃ̏���
	if (savePos.x - ReturnPos.x <= 1.0f &&
		savePos.z - ReturnPos.z <= 1.0f)
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