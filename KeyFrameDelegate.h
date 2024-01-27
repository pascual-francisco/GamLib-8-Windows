#include "stdafx.h"

	#ifndef KEYFRAMEDELEGATE_H
	#define KEYFRAMEDELEGATE_H

	class KeyFrameDelegate
	{
		public:
			__declspec(dllexport) KeyFrameDelegate();
			__declspec(dllexport) virtual ~KeyFrameDelegate();
			__declspec(dllexport) virtual void onForward();
			__declspec(dllexport) virtual void onBackward();
			__declspec(dllexport) virtual void onLoopForward();
			__declspec(dllexport) virtual void onLoopBackward();
	};
	#endif
