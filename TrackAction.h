#include "stdafx.h"

	#ifndef TRACKACTION_H
	#define TRACKACTION_H

	class TrackAction
	{
		public:
		bool active;
		int	destinationKey;
		int	pauseCounter;
		int	pauseTime;
		int	actualState;
		int	previousAction;
		int	direction;

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

		__declspec(dllexport) TrackAction(bool  alive = false,  int type = 0,  int activeDirection = 0,  int time = 0,  int key = 0);
		__declspec(dllexport) TrackAction(const TrackAction&);
		__declspec(dllexport) ~TrackAction();
		__declspec(dllexport) const TrackAction& operator=(const TrackAction&);
		__declspec(dllexport) bool operator==(const TrackAction&) const;
		__declspec(dllexport) bool operator<(const TrackAction&) const;
	};
	#endif
