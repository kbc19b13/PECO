#include "stdafx.h"
#include "Enemy/Kuma.h"
#include "Enemy/Move/KumaMoveCircle.h"

KumaMoveCircle::KumaMoveCircle(Kuma* kuma) :
	IKumaMove(kuma)
{
	m_initPos = m_kuma->GetPosition();
	m_kuma->SetPosition(m_initPos);
}

void KumaMoveCircle::Move()
{
	CVector3 pos = m_initPos;
	// 角度から移動用のベクトルを求めて描画座標に加算する
	// 度数法の角度を弧度法に変換
	float radius = m_Angle * 3.14f / 180.0f;

	// 三角関数を使用し、円の位置を割り出す。
	CVector3 add = CVector3::Zero();
	add.x = cos(radius) * 5.0f;
	add.y = sin(radius) * 5.0f;

	// 結果ででた位置を中心位置に加算し、それを描画位置とする
	pos.x = m_initPos.x + add.x;
	pos.y = m_initPos.y + add.y;

	// 向きを変える
	m_Angle += 10.0f;
	m_kuma->SetPosition(pos);
}