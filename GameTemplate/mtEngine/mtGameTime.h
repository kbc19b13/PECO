#pragma once
#include "mtEnginePreCompile.h"

/*　ゲーム時間クラス　*/

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
		//1フレームの経過時間を取得
		const float GetFrameDeltaTime() const
		{
			//固定FPSにする。可変は要検討。
			//return 1.0f / 30.0f;
			return m_oneframeTime; //(単位・秒)
		}

		void PushFrameDeltaTime(float deltaTime)
		{
			//受け取ったfloatの値をlistに登録する
			//1フレームの経過時間
			m_frameDeltaTimeQue.push_back(deltaTime);
			//listに30フレーム分溜まると計算して1フレームの平均をだす
			if (m_frameDeltaTimeQue.size() > 30.0f) {
				float totalTime = 0.0f;
				//list 分、回し、経過時間を調べる
				for (auto time : m_frameDeltaTimeQue) {
					totalTime += time;
				}
				//listの平均値をとる
				m_oneframeTime = min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
				//先頭から要素を削除していく
				m_frameDeltaTimeQue.pop_front();
			}
		}

		const float GetFrameRate() const
		{
			return m_fps;
		}

	private:
		//計算した1フレームの経過時間
		float m_oneframeTime = 1.0f / 60.0f;
		//1フレームの経過時間を格納するlist
		std::list<float> m_frameDeltaTimeQue;

		const float m_fps = 60.f;		//フレームレート。
	};
	static CGameTime& GameTime()
	{
		return CGameTime::GetInstance();
	}
}
