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
	/// <summary>
	//////////const変数を設定////////////
	/// </summary>
	/// 設定 → set
	/// 
	const float set_height = 50.0f;

	
	CVector3 target = m_player->GetPosition();

	old_pos = Camera_pos;

	target.y += set_height;

	Camera_pos = target + m_DiagonalFixed;
	

	g_camera3D.SetTarget(target);
	g_camera3D.SetPosition(Camera_pos);
	
	//カメラの更新。
	g_camera3D.Update();
}

