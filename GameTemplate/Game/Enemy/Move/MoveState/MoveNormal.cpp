#include "stdafx.h"
#include "MoveNormal.h"
#include "Enemy/Kuma.h"

MoveNormal::MoveNormal(Kuma* kuma) :
	IKumaMove(kuma)
{
	//通常アニメーションを流す
}


void MoveNormal::Move()
{
	/*通常状態の処理を記述する*/
	
	//初期座標を取得
	CVector3 savePos = m_kuma->GetSavePos();

	//if初期地にいる時は、移動処理を更新する？

	//if初期地から離れている時は、初期地に帰ってくる。

	
}