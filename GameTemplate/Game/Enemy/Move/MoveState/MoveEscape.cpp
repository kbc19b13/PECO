#include "stdafx.h"
#include "MoveEscape.h"
#include "Enemy/Kuma.h"

MoveEscape::MoveEscape(Kuma* kuma) :
	IKumaMove(kuma)
{
	m_player = Player::P_GetInstance();

	//アニメーションの再生
	//逃げる時のアニメーションを再生
	
}

void MoveEscape::Move()
{
	//逃走状態時の移動処理を記述
	//移動処理の記述
	
	//Discoveryから遷移→逃走

	//・Playerに捕まると拘束状態に遷移する
	//Playerの処理に記述→フラグを立てて処理分岐？


	//・一定距離離れると戻り状態に遷移する
	//MoveEscapeクラスないで処理移動処理があればMove関数に記述

	m_speed = { 1.0f, 0.0f, 0.0f };

	//クマの座標を更新
	m_kuma->AddPosition(m_speed);

	//Playerとクマとの距離を求めて、1000離れると戻り状態に切り替える。	
	if (GetDistance(m_player->GetPosition(), m_pos) > 1000.0f)
	{
		//距離が1000以上なら戻り状態に遷移する。
		//移動処理を戻り処理に切り替える。
		m_kuma->ExecuteFSM_Return();
	}
	
}