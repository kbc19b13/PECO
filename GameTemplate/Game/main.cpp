#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "BackGround.h"
#include "level/Level.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	//プレイヤー
	Player player;
	//背景
	BackGround background;


	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();

		//NewGO<Player>(0);

		//オブジェクトの更新。
		player.Update();
		background.Update();

		//オブジェクトの描画。
		player.Draw();
		background.Draw();

		//カメラの更新。
		g_camera3D.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}