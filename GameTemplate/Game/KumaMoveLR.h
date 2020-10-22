#pragma once

#include "Enemy/Move/IKumaMove.h"

class KumaMoveLR : public IKumaMove
{
public:
	KumaMoveLR(Kuma* kuma);

	void Move();
private:
	CVector3 m_initPos;
};

