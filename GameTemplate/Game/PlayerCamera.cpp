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
	m_player = FindGO<Player>("Player");

	
	g_camera3D.SetFar(10000.0f);
	
	return true;
}

void PlayerCamera::Update()
{
	CVector3 target = m_player->GetPosition();

	old_pos = GetPosition();

	target.y += 50.0f;

	Camera_pos = target + m_pos;

	g_camera3D.SetTarget(target);
	g_camera3D.SetPosition(Camera_pos);
	
	//カメラの更新。
	g_camera3D.Update();
}

