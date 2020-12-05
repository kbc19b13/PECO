#include "stdafx.h"
#include "Enemy/Kuma.h"
#include "Enemy/Move/KumaMoveCircle.h"

KumaMoveCircle::KumaMoveCircle(Kuma* kuma) :
	IKumaMove(kuma)
{
	m_initPos = m_kuma->GetPosition();
	m_kuma->SetPosition(m_initPos);
	pos = m_initPos;
}

void KumaMoveCircle::Move()
{
	
	// �p�x����ړ��p�̃x�N�g�������߂ĕ`����W�ɉ��Z����
	// �x���@�̊p�x���ʓx�@�ɕϊ�
	float radius = m_Angle * 3.14f / 180.0f;

	// �O�p�֐����g�p���A�~�̈ʒu������o���B
	CVector3 add = CVector3::Zero();
	add.x = cos(radius) * 5.0f;
	add.z = sin(radius) * 5.0f;

	// ���ʂłł��ʒu�𒆐S�ʒu�ɉ��Z���A�����`��ʒu�Ƃ���
	pos.x = m_initPos.x + add.x;
	pos.z = m_initPos.z + add.z;

	// ������ς���
	m_Angle += 10.0f;
	m_kuma->SetPosition(pos);
}