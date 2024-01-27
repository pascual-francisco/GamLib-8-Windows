#include "stdafx.h"

	#ifndef TIMERDELEGATE_H
	#define TIMERDELEGATE_H

	class TimerDelegate
	{
		public:
			__declspec(dllexport) TimerDelegate();
			__declspec(dllexport) ~TimerDelegate();
			__declspec(dllexport) virtual void onTick();
	};
	#endif
