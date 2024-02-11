#include "stdafx.h"

namespace time
{

	#ifndef TIMERDELEGATE_H
	#define TIMERDELEGATE_H

	class TimerDelegate: public Object
	{
		public:
		__declspec(dllexport) TimerDelegate();
		__declspec(dllexport) ~TimerDelegate();
		__declspec(dllexport) virtual void onTick();
	};
	#endif
}
