#include "stdafx.h"
#include "Player.h"
#include "..//mtEngine/mtGameTime.h"
//#include "..//mtEngine/mtStopwatch.h"


Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/PECO.cmo");
	
}


Player::~Player()
{
	DeleteGO("Player");
}

bool Player::Start()
{
	CCon.Init(30.0f, 160.0f, m_pos);
	
	return true;
}

void Player::Update()
{
	m_speed.x = g_pad[0].GetLStickXF() * -300.0f;
	m_speed.z = g_pad[0].GetLStickYF() * -300.0f;
	m_speed.y -= 980.0f * GameTime().GetFrameDeltaTime();

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

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	Draw();
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

//start
//update
/*
ondestroy
*/