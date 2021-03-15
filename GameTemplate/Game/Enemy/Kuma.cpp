#include "stdafx.h"
#include "Time/mtGameTime.h"
#include "Enemy/Kuma.h"
#include "Player.h"
#include "Move/KumaMoveUpDown.h"
#include "Move/KumaMoveLR.h"
#include "Move/KumaMoveCircle.h"
#include "Move/MoveState/MoveNormal.h"
#include "Move/MoveState/MoveDiscovery.h"
#include "Move/MoveState/MoveEscape.h"
#include "Move/MoveState/MoveReturn.h"


bool Kuma::Start()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/MoriKuma.cmo");

	//AnimationClipをロード(tkaファイルの読み込み)
	//Animaitonの初期化を行う
	//ファイル_アニメーションフレームメモ.txtに記載
	m_MoriAnimationClips[0].Load(L"Assets/animData/idle_Kuma.tka");
	m_MoriAnimationClips[0].SetLoopFlag(true);
	m_MoriAnimationClips[1].Load(L"Assets/animData/Walk_Kuma.tka");
	m_MoriAnimationClips[1].SetLoopFlag(true);
	m_MoriAnimationClips[2].Load(L"Assets/animData/Falldown_Kuma.tka");
	m_MoriAnimationClips[2].SetLoopFlag(true);
	m_MoriAnimationClips[3].Load(L"Assets/animData/Catch_Kuma.tka");
	m_MoriAnimationClips[3].SetLoopFlag(true);
	m_MoriAnimationClips[4].Load(L"Assets/animData/Wriggle_Kuma.tka");
	m_MoriAnimationClips[4].SetLoopFlag(true);
	m_MoriAnimationClips[5].Load(L"Assets/animData/DeathState_Kuma.tka");
	m_MoriAnimationClips[5].SetLoopFlag(true);
	m_MoriAnimationClips[6].Load(L"Assets/animData/Surprise_Kuma.tka");
	m_MoriAnimationClips[6].SetLoopFlag(false);
	//アニメーションの初期化
	m_MoriAnimation.Init(
		//アニメーションを流すスキンモデル(関連付け)
		m_model,
		//アニメーションクリップの配列
		m_MoriAnimationClips,
		//アニメーションクリップの数
		7
	);

	m_player = Player::P_GetInstance();

	return true;
}
////////////////移動処理//////////////////////
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

void Kuma::CreateMoveCircle()
{
	//移動処理のインスタンスを作成する。
	m_kumamove = std::make_unique<KumaMoveCircle>(this);
	m_movestate = State_Circle;
}
////////////////////////////////////////////
/////////////////状態処理///////////////////
void Kuma::ExecuteFSM_Normal()
{
	//元の移動状態に戻す
	switch (m_movestate) {

	case State_Circle:
		//円移動の処理を作成
		CreateMoveCircle();
		break;

	case State_LR:
		//左右移動の処理を作成
		CreateMoveLR();
		break;

	case State_UpDown:
		//上下移動の処理を作成
		CreateMoveUpDown();
		break;
	}
}
void Kuma::ExecuteFSM_Discovery()
{
	//待機状態のインスタンスを作成。
	m_kumamove = std::make_unique<MoveDiscovery>(this);
	m_state = State_Discovery;
}
void Kuma::ExecuteFSM_Escape()
{
	//逃げ状態のインスタンスを作成。
	m_kumamove = std::make_unique<MoveEscape>(this);
	m_state = State_Escape;
}
void Kuma::ExecuteFSM_Return()
{
	//戻り状態のインスタンスを作成。
	m_kumamove = std::make_unique<MoveReturn>(this);
	m_state = State_Return;
}
////////////////////////////////////////////////
void Kuma::Update()
{
	//フレームレート対応変数
	float frametime = GameTime().GetFrameDeltaTime();
	
	//クマの移動処理を実行する。
	if (m_kumamove) {
		//クマの移動処理を実行する。
		m_kumamove->Move();
	}

	//Playerとクマとの距離を求めて処理を行う
	//Playerの座標を取得する処理が入るので
	if (GetDistance(m_player->GetPosition(), m_pos) < 100.0f)
	{
		//距離が100以下なら逃げ状態に遷移する。
		//移動処理を逃げる処理に切り替える。
		ExecuteFSM_Discovery();
	}
	
	//ステートマシン
	ExecuteFSM();

	//アニメーションの再生
	m_MoriAnimation.Update(frametime);
	//シャドウキャスターに登録
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	//座標を更新
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	//通常描画
	Draw(enRenderMode_Normal);
}
void Kuma::ExecuteFSM()
{
	switch (m_state) {

	case State_Normal:
		//通常状態
		ExecuteFSM_Normal();
		break;

	case State_Discovery:
		//発見状態
		ExecuteFSM_Discovery();
		break;

	case State_Escape:
		//逃げ状態
		ExecuteFSM_Escape();
		break;

	case State_Return:
		//戻り状態
		ExecuteFSM_Return();
		break;

	}

}
