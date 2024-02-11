#include "stdafx.h"

namespace time
{
	#ifndef TIMER_H
	#define TIMER_H

	class Timer: public Object
	{
		private:
		LARGE_INTEGER inTime;
		LARGE_INTEGER outTime;
		LARGE_INTEGER frameTime;
		LARGE_INTEGER frequency;
		uint actualFrame;
		uint frameRate;
		
		public:
		vector<TimerDelegate*> timerDelegate;

		__declspec(dllexport)  Timer(unsigned int = 30);
		__declspec(dllexport) ~Timer();
		__declspec(dllexport) void update();
	};
	#endif
}
