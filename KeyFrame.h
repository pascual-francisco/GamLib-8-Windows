#include "stdafx.h"
	
namespace animation
{
	#ifndef KEYFRAME_H
	#define KEYFRAME_H

	class KeyFrame: public Object
	{
		public:
		enum EasingMode
		{
			LINEAR, ACCELERATION, DECELERATION, SMOOTHSTEP, DISCRETE
		};

		TrackAction					action;
		float						value;
		float						time;
		vector<KeyFrameDelegate*>	keyDelegate;

		int	easingForward;
		int	easingReverse;

		__declspec(dllexport) KeyFrame(float keyTime = 0.0f, float keyValue = 0.0f, int easingF = 0, int easingR = 0, bool actionActive = false, int actionState = 0, int fireDirection = 0, float time = 0.0f, int key = 0);

		__declspec(dllexport) KeyFrame(const KeyFrame& key);
		__declspec(dllexport) ~KeyFrame();

		__declspec(dllexport) void init(float keyTime = 0.0f, float keyValue = 0.0f, int easingF = 0, int easingR = 0, bool actionActive = false, int actionState = 0, int fireDirection = 0, float time = 0.0f, int key = 0);
		__declspec(dllexport) void reset();
		__declspec(dllexport) const KeyFrame& operator=(const KeyFrame& key);
		__declspec(dllexport) bool operator==(const KeyFrame& key) const;
		__declspec(dllexport) bool operator<(const KeyFrame& key) const;
		__declspec(dllexport) bool operator>(const KeyFrame& key) const;
	};
#endif
}
