#include "stdafx.h"
#include "MoveNormal.h"
#include "Enemy/Kuma.h"

MoveNormal::MoveNormal(Kuma* kuma) :
	IKumaMove(kuma)
{
	//�ʏ�A�j���[�V�����𗬂�
}


void MoveNormal::Move()
{
	/*�ʏ��Ԃ̏������L�q����*/
	
	//�������W���擾
	CVector3 savePos = m_kuma->GetSavePos();

	//if�����n�ɂ��鎞�́A�ړ��������X�V����H

	//if�����n���痣��Ă��鎞�́A�����n�ɋA���Ă���B

	if (m_kuma->PE_GetDistance() < 100.0f)
	{
		//������100�ȉ��Ȃ瓦����ԂɑJ�ڂ���B
		//�ړ������𓦂��鏈���ɐ؂�ւ���B
		m_kuma->ExecuteFSM_Discovery();
	}
}