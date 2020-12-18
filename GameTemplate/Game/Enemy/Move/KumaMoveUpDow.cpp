#include "stdafx.h"
#include "Enemy/Kuma.h"
#include "Enemy/Move/KumaMoveUpDown.h"


KumaMoveUpDown::KumaMoveUpDown(Kuma* kuma) :
	IKumaMove(kuma)	//���N���X�̃R���X�g���N�^�𖾎��I�ɌĂяo���B
{
	//�������W���L�^���Ă����B
	m_initPos = m_kuma->GetPosition();
}
void KumaMoveUpDown::Move()
{
	static float t = 0.0f;
	t += 0.01f;
	float up = sinf(t);
	CVector3 pos = m_initPos;
	pos.y += up * 1.0f;
	m_kuma->SetPosition(pos);
}