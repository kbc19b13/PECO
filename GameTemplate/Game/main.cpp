#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "level/Level.h"
//#include "../mtEngine/Stopwatch.h"
//#include "../mtEngine/mtGameTime.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	
	NewGO<Game>(0, "Game");

	//Hands-On ���̃��m����O�ɕ`�悷��[�x�X�e���V���X�e�[�g������Ă݂悤�B
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

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//m_sw.Start();

		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();

		GameObjectManager().ExecuteFromMainThread();
		GameObjectManager().ExecuteFromGameThread();

		//�`��I���B
		g_graphicsEngine->EndRender();

		//m_sw.Stop();

		 //GameTime().PushFrameDeltaTime((float)m_sw.GetElapsedSecond());
	}
}