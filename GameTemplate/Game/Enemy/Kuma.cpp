#include "stdafx.h"
#include "Enemy/Kuma.h"

#include "Move/KumaMoveUpDown.h"
#include "Move/KumaMoveLR.h"
#include "Move/KumaMoveCircle.h"


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
		g_camera3D.GetProjectionMatrix()
	);
}
void Kuma::Update()
{

	//クマの移動処理を実行する。
	if (m_move) {
		//クマの移動処理を実行する。
		m_move->Move();
	}

	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	Draw();
}