#pragma once
#include "Player.h"

class PlayerCamera : public IGameObject
{
public:
	PlayerCamera();
	~PlayerCamera();

	void Update();
	bool Start();
	/// <summary>
	/// カメラの更新処理
	/// </summary>
	void CameraUpdate();

private:
	//一つ前のカメラ座標
	CVector3 old_pos = { 0.0f, 0.0f, 0.0f };
	//カメラの座標
	CVector3 Camera_pos = { 0.0f, 200.0f, 300.0f };

private:
	//スキンモデル
	SkinModel m_model;

private:
	Player* m_player = nullptr;

};

