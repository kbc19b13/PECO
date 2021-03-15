#pragma once
#include "mtEnginePreCompile.h"
//#include <WinSock2.h>
//#include <windows.h>
//#include <WinSock2.h>
//#include <windows.h>
/*　ストップウォッチクラス　*/

namespace mtEngine {
	
	
	/*サンプルコード
		Stopwatch sw;
	sw.Start();		//計測開始。
	for (int i = 0; i < 100; i++) {
	}
	sw.Stop();		//計測終了
	printf("経過時間 = %lf(単位：秒)\n", sw.GetElapsed());
	printf("経過時間 = %lf(単位：ミリ)\n", sw.GetElapsedMillisecond());*/
	

	class CStopwatch
	{
	public:
		CStopwatch()
		{
			freq = 0;
			end = 0;
			begin = 0;
			elapsed = 0.0;
			Mill_elapsed = 0.0;
			Micro_elapsed = 0.0;
		}

		~CStopwatch()
		{}

		void Start()
		{
			::QueryPerformanceCounter((LARGE_INTEGER*)& begin);
		}

		void Stop()
		{
			::QueryPerformanceFrequency((LARGE_INTEGER*)& freq);
			::QueryPerformanceCounter((LARGE_INTEGER*)& end);
			elapsed = double(end - begin) / freq;
			Mill_elapsed = elapsed * 1000.0;
			Micro_elapsed = Mill_elapsed * 1000.0;
		}
		

		//経過時間を取得
		double GetElapsedSecond() const
		{
			return elapsed;
		}

		//経過時間を取得(単位:ミリ秒)
		double GetElapsedMillisecond() const
		{
			return Mill_elapsed;
		}

		//経過時間を取得(単位:マイクロ秒)
		double GetElapsedMicrosecond() const
		{
			return Micro_elapsed;
		}

		  
	private:
		LONGLONG freq;
		LONGLONG end;
		LONGLONG begin;
		//経過時間(単位：秒)
		double elapsed = 0.0f;		
		//経過時間(単位：ミリ秒)
		double Mill_elapsed = 0.0f; 
		//経過時間(単位：マイクロ秒)
		double Micro_elapsed = 0.0f;		
	};



}

