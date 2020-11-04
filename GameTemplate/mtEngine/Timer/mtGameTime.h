#pragma once
#include "mtEnginePreCompile.h"

/*�@�Q�[�����ԃN���X�@*/

namespace mtEngine
{
	class CGameTime
	{
		CGameTime()
		{}
		~CGameTime()
		{}

	public:
		static CGameTime& GetInstance()
		{
			static CGameTime t;
			return t;
		}
	public:
		//1�t���[���̌o�ߎ��Ԃ��擾
		const float GetFrameDeltaTime() const
		{
			//�Œ�FPS�ɂ���B�ς͗v�����B
			//return 1.0f / 30.0f;
			return m_oneframeTime; //(�P�ʁE�b)
		}

		void PushFrameDeltaTime(float deltaTime)
		{
			//�󂯎����float�̒l��list�ɓo�^����
			//1�t���[���̌o�ߎ���
			m_frameDeltaTimeQue.push_back(deltaTime);
			//list��30�t���[�������܂�ƌv�Z����1�t���[���̕��ς�����
			if (m_frameDeltaTimeQue.size() > 30.0f) {
				float totalTime = 0.0f;
				//list ���A�񂵁A�o�ߎ��Ԃ𒲂ׂ�
				for (auto time : m_frameDeltaTimeQue) {
					totalTime += time;
				}
				//list�̕��ϒl���Ƃ�
				m_oneframeTime = min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
				//�擪����v�f���폜���Ă���
				m_frameDeltaTimeQue.pop_front();
			}
		}

		const float GetFrameRate() const
		{
			return m_fps;
		}

	private:
		//�v�Z����1�t���[���̌o�ߎ���
		float m_oneframeTime = 1.0f / 60.0f;
		//1�t���[���̌o�ߎ��Ԃ��i�[����list
		std::list<float> m_frameDeltaTimeQue;

		const float m_fps = 60.f;		//�t���[�����[�g�B
	};
	static CGameTime& GameTime()
	{
		return CGameTime::GetInstance();
	}
}
