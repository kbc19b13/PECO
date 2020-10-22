#include "stdafx.h"
#include "Enemy/Kuma.h"
#include "KumaMoveLR.h"

KumaMoveLR::KumaMoveLR(Kuma* kuma):
	IKumaMove(kuma)
{
	m_initPos = m_kuma->GetPosition();
}

void KumaMoveLR::Move()
{
	static float t = 0.0f;
	t += 0.01f;
	float up = sinf(t);
	CVector3 pos = m_initPos;
	pos.y += up * 10.0f;
	m_kuma->SetPosition(pos);
}