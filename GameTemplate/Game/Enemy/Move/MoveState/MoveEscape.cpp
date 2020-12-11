#include "stdafx.h"
#include "MoveEscape.h"
#include "Enemy/Kuma.h"

MoveEscape::MoveEscape(Kuma* kuma) :
	IKumaMove(kuma)
{
	//アニメーションの再生
	//逃げる時のアニメーションを再生
	
}

void MoveEscape::Move()
{
	//逃走状態時の移動処理を記述
	//移動処理の記述
	
	m_kuma->AddPosition({ 1.0f, 0.0f, 0.0f });
}