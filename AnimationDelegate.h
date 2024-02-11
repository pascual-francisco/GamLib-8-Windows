#pragma once

#include "stdafx.h"

namespace animation
{
	#ifndef ANIMATIONDELEGATE_H
	#define ANIMATIONDELEGATE_H

	class AnimationDelegate
	{
		public:
		__declspec(dllexport) AnimationDelegate();
		__declspec(dllexport) virtual ~AnimationDelegate();
		__declspec(dllexport) virtual void onForward();
		__declspec(dllexport) virtual void onBackward();
		__declspec(dllexport) virtual void onLoopForward();
		__declspec(dllexport) virtual void onLoopBackward();
		__declspec(dllexport) virtual void onStop();
		__declspec(dllexport) virtual void onPause();
	};
	#endif
}
