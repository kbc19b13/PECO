#include "stdafx.h"
#include "..//mtEngine/mtGameTime.h"
#include "MoveDiscovery.h"
#include "Enemy/Kuma.h"


MoveDiscovery::MoveDiscovery(Kuma* kuma) :
	IKumaMove(kuma)
{
	//アニメーションの処理
	//ビックリしているアニメーションと
	//エフェクトを流す。
	//ビックリアニメーションを再生
	m_kuma->SetAnimation(6);
}


void MoveDiscovery::Move()
{
	//Normalから遷移→待機、遅延
	//終了するとEscapeに遷移する。
	//↓MoveDiscoveryクラスないで処理移動処理があればMove関数に記述
	//アニメーションの再生→ビックリアニメーション。
	//エフェクトの再生→ビックリアイコン

	//待機時の移動処理を記述
	//計測と遷移はkumaクラスが責任を持つ→遷移クラスの作成？
	m_kuma->AddTime(GameTime().GetFrameDeltaTime());
	int a = 0;

	//一秒待機させる。
	if (m_kuma->GetFrameTime() >= 1.0f)
	{
		/*ここに遅延後の処理を描く*/

		//待機時間を初期値にする。
		m_kuma->SetFrameTime(0.0f);
		//通常アニメーションを再生
		m_kuma->SetAnimation(0);

		//発見状態が終わって逃げ状態に遷移する。
		m_kuma->ExecuteFSM_Escape();
	}
}