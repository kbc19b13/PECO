#include "stdafx.h"
#include "..//mtEngine/mtGameTime.h"
#include "Enemy/Kuma.h"
#include "Player.h"
#include "Move/KumaMoveUpDown.h"
#include "Move/KumaMoveLR.h"
#include "Move/KumaMoveCircle.h"
#include "Move/MoveState/MoveNormal.h"
#include "Move/MoveState/MoveDiscovery.h"
#include "Move/MoveState/MoveEscape.h"


bool Kuma::Start()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/MoriKuma.cmo");

	//AnimationClipをロード(tkaファイルの読み込み)
	//Animaitonの初期化を行う
	//ファイル_アニメーションフレームメモ.txtに記載
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

	//SavePos = GetPosition();

	m_player = Player::P_GetInstance();

	return true;
}
void Kuma::CreateMoveUpDown()
{
	//移動処理のインスタンスを作成する。
	m_kumamove = std::make_unique< KumaMoveUpDown >(this);
	m_movestate = State_UpDown;
}

void Kuma::CreateMoveLR()
{
	//移動処理のインスタンスを作成する。
	m_kumamove = std::make_unique<KumaMoveLR>(this);
	m_movestate = State_LR;
}

void Kuma::CreateMoveTrun()
{
	//移動処理のインスタンスを作成する。
	m_kumamove = std::make_unique<KumaMoveCircle>(this);
	m_movestate = State_Circle;
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
		m_kumamove = std::make_unique<MoveDiscovery>(this);
		m_state = State_Discovery;
	}

}
void Kuma::ExecuteFSM_Discovery()
{
	//Normalから遷移→待機、遅延
	//終了するとEscapeに遷移する。
	
	//アニメーションの再生→ビックリアニメーション。
	//エフェクトの再生→ビックリアイコン

	frametime += GameTime().GetFrameDeltaTime();

	if (frametime <= 1.0f)
	{
		//ここに遅延後の処理を描く
		//発見状態が終わって逃げ状態に遷移する。
		m_kumamove = std::make_unique<MoveEscape>(this);
		m_state = State_Escape;

		frametime = 0.0f;
	}

}

void Kuma::ExecuteFSM_Escape()
{
	//逃げ切ったら、通常状態に戻る

	//プレイヤーとの距離を判定して、一定距離以下だったら逃げ状態に遷移するようにしてください。
	CVector3 player_pos = m_player->GetPosition();
	//プレイヤーからエネミーに伸びるベクトルを計算。
	CVector3 enemyToPlayerVec = player_pos - m_pos;
	//プレイヤーとエネミーの距離を計算。
	float distance = enemyToPlayerVec.Length();
	
	if( distance > 1000.0f )
	{
		//距離が100以上なら通常状態に遷移する。
		//移動処理を通常処理に切り替える。
		m_kumamove = std::make_unique<MoveNormal>(this);
		m_state = State_Normal;
	}
	

}
void Kuma::ExecuteFSM()
{
	switch (m_state) {
	
	case State_Normal:
		//通常状態
		ExecuteFSM_Normal();
		
		//初期状態に戻った時に判定を行う…
		/*
			//通常状態に戻った時の移動状態に修正
			switch (m_movestate) {
			case State_Circle:
				CreateMoveTrun();
				break;

			case State_LR:
				CreateMoveLR();
				break;

			case State_UpDown:
				CreateMoveUpDown();
				break;

			}
		*/
		

		break;

	case State_Discovery:
		//発見状態
		ExecuteFSM_Discovery();
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
	if (m_kumamove) {
		//クマの移動処理を実行する。
		m_kumamove->Move();
	}
	ExecuteFSM();
	
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	Draw(0);
}