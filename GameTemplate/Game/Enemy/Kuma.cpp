#include "stdafx.h"
#include "Enemy/Kuma.h"
#include "Player.h"
#include "Move/KumaMoveUpDown.h"
#include "Move/KumaMoveLR.h"
#include "Move/KumaMoveCircle.h"
#include "Move/MoveState/MoveEscape.h"

bool Kuma::Start()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/MoriKuma.cmo");

	//AnimationClipをロード(tkaファイルの読み込み)
	//Animaitonの初期化を行う
	m_MoriAnimationClips[0].Load(L"Assets/animData/Walk_Kuma.tka");
	m_MoriAnimationClips[0].SetLoopFlag(true);
	m_MoriAnimationClips[1].Load(L"Assets/animData/Falldown_Kuma.tka");
	m_MoriAnimationClips[1].SetLoopFlag(true);
	m_MoriAnimationClips[2].Load(L"Assets/animData/Catch_Kuma.tka");
	m_MoriAnimationClips[2].SetLoopFlag(true);
	m_MoriAnimationClips[3].Load(L"Assets/animData/Wriggle_Kuma.tka");
	m_MoriAnimationClips[3].SetLoopFlag(true);
	m_MoriAnimationClips[4].Load(L"Assets/animData/DeathState_Kuma.tka");
	m_MoriAnimationClips[4].SetLoopFlag(true);
	//アニメーションの初期化
	m_MoriAnimation.Init(
		//アニメーションを流すスキンモデル(関連付け)
		m_model,
		//アニメーションクリップの配列
		m_MoriAnimationClips,
		//アニメーションクリップの数
		5
	);

	m_player = Player::P_GetInstance();

	return true;
}
void Kuma::CreateMoveUpDown()
{
	//移動処理のインスタンスを作成する。
	m_move = std::make_unique< KumaMoveUpDown >(this);
}

void Kuma::CreateMoveLR()
{
	m_move = std::make_unique<KumaMoveLR>(this);
}

void Kuma::CreateMoveTrun()
{
	m_move = std::make_unique<KumaMoveCircle>(this);
}

void Kuma::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
}

void Kuma::ExecuteFSM_Normal()
{
	//プレイヤーとの距離を判定して、一定距離以下だったら逃げ状態に遷移するようにしてください。
	CVector3 player_pos = m_player->GetPosition();
	//プレイヤーからエネミーに伸びるベクトルを計算。
	CVector3 enemyToPlayerVec = player_pos - m_pos;
	//プレイヤーとエネミーの距離を計算。
	float distance = enemyToPlayerVec.Length();
	if (distance < 100.0f)
	{
		//距離が100以下なら逃げ状態に遷移する。
		//移動処理を逃げる処理に切り替える。
		m_move = std::make_unique<MoveEscape>(this);
		m_state = State_Escape;
	}

}

void Kuma::ExecuteFSM_Escape()
{
	//逃げ切ったら、通常状態に戻る
	//if( )
}
void Kuma::ExecuteFSM()
{
	switch (m_state) {
	case State_Normal:
		//通常
		ExecuteFSM_Normal();
		break;
	case State_Escape:
		//逃げ状態
		ExecuteFSM_Escape();
		break;
	}

}
void Kuma::Update()
{
	//クマの移動処理を実行する。
	if (m_move) {
		//クマの移動処理を実行する。
		m_move->Move();
	}
	ExecuteFSM();
	
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	Draw();
}