#include "stdafx.h"
#include "PlayerCamera.h"

PlayerCamera::PlayerCamera()
{

}
PlayerCamera::~PlayerCamera()
{

}

bool PlayerCamera::Start()
{
	/// <summary>
	//////////const変数を設定////////////
	/// </summary>
	/// 設定 → set
	/// 
	//遠平面を設定
	const float set_far = 10000.0f;


	//Playerのインスタンスを取得
	m_player = Player::P_GetInstance();

	
	g_camera3D.SetFar(set_far);
	
	return true;
}

void PlayerCamera::Update()
{
	//注視点の高さを設定
	const float set_height = 50.0f;

	//カメラを更新。
	//注視点を計算する。
	CVector3 target = m_player->GetPosition();
	//一つ前のpositionに置き換える
	old_pos = Camera_pos;

	CameraUpdate();

	target.y = set_height;
	CVector3 pos = target + Camera_pos;

	g_camera3D.SetTarget(target);
	g_camera3D.SetPosition(pos);
	
	//カメラの更新。
	g_camera3D.Update();
}
void PlayerCamera::CameraUpdate()
{
	//カメラの上方向を設定
	const CVector3 set_Up = { 0.0f,  1.0f,  0.0f };

	//パッドの入力でカメラを回転
	float rStickX = g_pad[0].GetRStickXF();
	float rStickY = g_pad[0].GetRStickYF();

	//上下のカメラ回転
	CQuaternion rot;
	rot.SetRotationDeg(set_Up, 0.5f * rStickX);
	rot.Apply(Camera_pos);

	//左右のカメラ回転
	CVector3 rotAxis;
	rotAxis.Cross(Camera_pos, { 0.0f, 1.0f, 0.0f });
	rotAxis.Normalize();//単位ベクトルに変化
	rot.SetRotationDeg(rotAxis, 0.5f * rStickY);
	rot.Apply(Camera_pos);

	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	CVector3 toPosDir = Camera_pos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.1f) {
		//カメラが上向きすぎ。
		Camera_pos = old_pos;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		Camera_pos = old_pos;
	}
}
