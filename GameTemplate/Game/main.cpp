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

	//Hands-On 奥のモノを手前に描画する深度ステンシルステートを作ってみよう。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc = D3D11_COMPARISON_GREATER;
	desc.StencilEnable = false;
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

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