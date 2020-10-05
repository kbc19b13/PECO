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