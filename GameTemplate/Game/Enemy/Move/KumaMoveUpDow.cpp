#include "stdafx.h"
#include "Enemy/Kuma.h"
#include "Enemy/Move/KumaMoveUpDown.h"


KumaMoveUpDown::KumaMoveUpDown(Kuma* kuma) :
	IKumaMove(kuma)	//基底クラスのコンストラクタを明示的に呼び出す。
{
	//初期座標を記録しておく。
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