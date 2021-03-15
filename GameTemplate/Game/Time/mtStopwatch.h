#pragma once
#include "mtEnginePreCompile.h"
//#include <WinSock2.h>
//#include <windows.h>
//#include <WinSock2.h>
//#include <windows.h>
/*�@�X�g�b�v�E�H�b�`�N���X�@*/

namespace mtEngine {
	
	
	/*�T���v���R�[�h
		Stopwatch sw;
	sw.Start();		//�v���J�n�B
	for (int i = 0; i < 100; i++) {
	}
	sw.Stop();		//�v���I��
	printf("�o�ߎ��� = %lf(�P�ʁF�b)\n", sw.GetElapsed());
	printf("�o�ߎ��� = %lf(�P�ʁF�~��)\n", sw.GetElapsedMillisecond());*/
	

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
		

		//�o�ߎ��Ԃ��擾
		double GetElapsedSecond() const
		{
			return elapsed;
		}

		//�o�ߎ��Ԃ��擾(�P��:�~���b)
		double GetElapsedMillisecond() const
		{
			return Mill_elapsed;
		}

		//�o�ߎ��Ԃ��擾(�P��:�}�C�N���b)
		double GetElapsedMicrosecond() const
		{
			return Micro_elapsed;
		}

		  
	private:
		LONGLONG freq;
		LONGLONG end;
		LONGLONG begin;
		//�o�ߎ���(�P�ʁF�b)
		double elapsed = 0.0f;		
		//�o�ߎ���(�P�ʁF�~���b)
		double Mill_elapsed = 0.0f; 
		//�o�ߎ���(�P�ʁF�}�C�N���b)
		double Micro_elapsed = 0.0f;		
	};



}

