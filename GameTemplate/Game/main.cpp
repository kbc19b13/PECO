#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "level/Level.h"
//#include "../mtEngine/Stopwatch.h"
//#include "../mtEngine/mtGameTime.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	
	NewGO<Game>(0, "Game");

	//CStopwatch m_sw;

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//m_sw.Start();

		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();

		GameObjectManager().ExecuteFromMainThread();
		GameObjectManager().ExecuteFromGameThread();

		//描画終了。
		g_graphicsEngine->EndRender();

		//m_sw.Stop();

		 //GameTime().PushFrameDeltaTime((float)m_sw.GetElapsedSecond());
	}
}