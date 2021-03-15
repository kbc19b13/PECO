#include "stdafx.h"
#include "Player.h"
#include "Time/mtGameTime.h"
//#include "..//mtEngine/mtStopwatch.h"

//グローバルにPlayerは一人だけ
Player* Player::m_instance = nullptr;

Player::Player()
{
	//インスタンスの制限
	if (m_instance != nullptr)
	{
		//2体目からはエラーが出る
		std::abort();
	}
	
	//Playerを固定
	m_instance = this;
}


Player::~Player()
{
	DeleteGO("Player");
}

bool Player::Start()
{
	const float CCon_radius = 30.0f;
	const float height = 160.0f;

	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/PECO.cmo");
	
	//AnimationClipをロード(tkaファイルの読み込み)
	//Animaitonの初期化を行う
	m_PlayerAnimationClips[0].Load(L"Assets/animData/Walk_PECO.tka");
	m_PlayerAnimationClips[0].SetLoopFlag(true);
	m_PlayerAnimationClips[1].Load(L"Assets/animData/Sneak_PECO.tka");
	m_PlayerAnimationClips[1].SetLoopFlag(true);
	m_PlayerAnimationClips[2].Load(L"Assets/animData/Cat_PECO.tka");
	m_PlayerAnimationClips[2].SetLoopFlag(true);
	m_PlayerAnimationClips[3].Load(L"Assets/animData/Extraction_PECO.tka");
	m_PlayerAnimationClips[3].SetLoopFlag(true);
	//アニメーションの初期化
	m_PlayerAnimation.Init(
		//アニメーションを流すスキンモデル(関連付け)
		m_model,
		//アニメーションクリップの配列
		m_PlayerAnimationClips,
		//アニメーションクリップの数
		4
	);

	//Playerをシャドウレシーバーにする。
	m_model.SetShadowReciever(true);

	m_CCon.Init(CCon_radius, height, m_pos);
	
	return true;
}

void Player::Update()
{
	//変数
	frametime = GameTime().GetFrameDeltaTime();

	//方向の取得処理
	Direction();
	//移動処理
	Move();
	//アニメーション再生
	Anim();

	//アニメーションの再生
	m_PlayerAnimation.Update(frametime);

	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
	
	renderMode = enRenderMode_Silhouette;
	Draw(renderMode);

	renderMode = enRenderMode_Normal;
	Draw(renderMode);
}

void Player::Direction()
{
	//Quaternionの回転から行列に変換
	p_rot.MakeRotationFromQuaternion(m_rot);

	//前方向正規化ベクトルの取得
	p_mae.x = p_rot.m[2][0];
	p_mae.y = p_rot.m[2][1];
	p_mae.z = p_rot.m[2][2];
	p_mae.Normalize();

	//上方向正規化ベクトルの取得
	p_ue.x = p_rot.m[1][0];
	p_ue.y = p_rot.m[1][1];
	p_ue.z = p_rot.m[1][2];
	p_ue.Normalize();

	//右方向正規化ベクトルの取得
	p_migi.x = p_rot.m[0][0];
	p_migi.y = p_rot.m[0][1];
	p_migi.z = p_rot.m[0][2];
	p_migi.Normalize();
}
void Player::Move()
{
	//定数
	const float playerSpeed = -200.0f;
	const float gravity = 980.0f;

	//スティックでの移動
	float lStickY = g_pad[0].GetLStickYF();
	float lStickX = -g_pad[0].GetLStickXF();

	//カメラの前方方向と右方向を取得。
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_speed.x = 0.0f;
	m_speed.z = 0.0f;
	//p_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	m_speed += cameraForward * lStickY * playerSpeed;	//奥方向への移動速度を代入。
	m_speed += cameraRight * lStickX * -playerSpeed;		//右方向への移動速度を加算。
	

	if (fabsf(m_speed.x) < 0.001f
		&& fabsf(m_speed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(m_speed.x, m_speed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rot.SetRotation(CVector3::AxisY(), angle);

	//moveSpeedでpositionを動かす
	m_pos += m_speed;
}
void Player::Anim()
{
	m_pos = m_CCon.Execute(frametime, m_speed);

	//true = 地面にいる
	if(m_CCon.IsOnGround() == true)
	{
		m_PlayerAnimation.Play(0);
	}
	if (g_pad[0].IsPress(enButtonB))
	{
		m_PlayerAnimation.Play(1);
	}
	/*if (g_pad[0].IsPress(enButtonLeft)) {
		m_pos.x += 5.0f;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		m_pos.x -= 5.0f;
	}
	if (g_pad[0].IsPress(enButtonUp)) {
		m_pos.z += 5.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		m_pos.z -= 5.0f;
	}*/

	
}