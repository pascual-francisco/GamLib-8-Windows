#include "stdafx.h"

	TrackAction::TrackAction(bool alive,  int type,  int fireDirection,  int time,  int k)
	{
		active = alive;
		direction = fireDirection;
		actualState = type;
		pauseTime = time;
		pauseCounter = 0;
		previousAction = FORWARD;
		destinationKey = (k>0?k:0);
	}

	TrackAction::TrackAction(const TrackAction &e)
	{
		if(&e!=this)
		{
			active = e.active;
			direction = e.direction;
			actualState = e.actualState;
			pauseTime = e.pauseTime;
			pauseCounter = e.pauseCounter;
			previousAction = e.previousAction;
			destinationKey = e.destinationKey;
		}
	}

	TrackAction::~TrackAction()
	{

	}

	const TrackAction& TrackAction::operator =(const TrackAction &e)
	{
		if(&e!=this)
		{
			active = e.active;
			direction = e.direction;
			actualState = e.actualState;
			pauseTime = e.pauseTime;
			pauseCounter = e.pauseCounter;
			previousAction = e.previousAction;
			destinationKey = e.destinationKey;
		}
		return *this;
	}

	bool TrackAction::operator==(const TrackAction &e) const
	{
		if(active == e.active &&
			direction == e.direction &&
			actualState == e.actualState &&
			pauseTime == e.pauseTime &&
			pauseCounter == e.pauseCounter &&
			destinationKey  ==  e.destinationKey)
		{
			return true;
		}
		else
		{
			return true;
		}
	}

	bool TrackAction::operator <(const TrackAction &e) const
	{
		if(pauseTime < e.pauseTime)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


