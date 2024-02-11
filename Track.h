#include "stdafx.h"

namespace animation
{
	#ifndef TRACK_H
	#define TRACK_H

	class Track : public Object
	{
		private:
		KeyFrame				PK;
		KeyFrame				NK;
		float					derivative;
		float					timeDerivative;
		int						keyIndex;

		public:
		bool					loop;
		int						keys;
		vector<KeyFrame>		keyFrames;
		float					frames;
		float					head;
		float					value;
		float					time;
		bool					constant;
		vector<TrackDelegate*>	trackDelegate;
		int						frameTime;
		int						frameCounter;
		int						actualState;

		enum TrackStates
		{
			FORWARD,
			BACKWARD,
			PAUSE,
			STOP,
			PAUSE_FORWARD,
			PAUSE_BACKWARD,
			LOOP_FORWARD,
			LOOP_BACKWARD,
			GO_TO_KEY,
			GO_TO_KEY_FORWARD,
			GO_TO_KEY_BACKWARD,
			GO_TO_KEY_LOOP_FORWARD,
			GO_TO_KEY_LOOP_BACKWARD,
			GO_TO_KEY_STOP,
		};

		__declspec(dllexport) Track(int frames = 0, int keys = 0, int frameTime = 0, int state = 3, bool constant = false, float value = 0.0f);
		__declspec(dllexport) Track(const Track&);
		__declspec(dllexport) ~Track();
		__declspec(dllexport) const Track& operator=(const Track&);
		__declspec(dllexport) bool operator==(const Track&) const;
		__declspec(dllexport) bool operator<(const Track&) const;

		__declspec(dllexport) void init(int frames = 0, int keys = 0, int frameTime = 0, int state = 3, bool constant = false, float value = 0.0f);
		__declspec(dllexport) void updateEvent();
		__declspec(dllexport) void applyDerivative();
		__declspec(dllexport) void calculateDerivative();
		__declspec(dllexport) void forward();
		__declspec(dllexport) void backward();
		__declspec(dllexport) void pause();
		__declspec(dllexport) void stop();
		__declspec(dllexport) void goToKey(int key = 0);
		__declspec(dllexport) void goToKeyAndForward(int key = 0);
		__declspec(dllexport) void goToKeyAndBackward(int key = 0);
		__declspec(dllexport) void goToKeyAndStop(int key = 0);
		__declspec(dllexport) void goToFirstKey();
		__declspec(dllexport) void goToFirstKeyAndStop();
		__declspec(dllexport) void goToFirstKeyAndBackward();
		__declspec(dllexport) void goToFirstKeyAndForward();
		__declspec(dllexport) void goToLastKey();
		__declspec(dllexport) void goToLastKeyAndStop();
		__declspec(dllexport) void goToLastKeyAndBackward();
		__declspec(dllexport) void goToLastKeyAndForward();
		__declspec(dllexport) void update();
		__declspec(dllexport) void print() const;
	};
	#endif
}