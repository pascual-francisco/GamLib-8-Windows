#include "stdafx.h"

	Track::Track(int frames,int keys,int frameTime, int state, bool constant, float value)
	{
		frames = 0;
		keys = 0;
		frameTime = 0;
		actualState = 0;
		head = 0;
		keyIndex = 0;
		derivative = 0.0f;
		timeDerivative = 0.0f;
		value = 0.0f;
		loop = false;
		frameCounter = 0;
		constant = 0;
		time = 0;
		init(frames, keys, frameTime, state, constant, value);
	}

	Track::Track(const Track& t)
	{
		if(&t != this)
		{
			frameCounter = t.frameCounter;
			frameTime = t.frameTime;
			trackDelegate = t.trackDelegate;
			value = t.value;
			derivative = t.derivative;
			timeDerivative = t.timeDerivative;
			constant = t.constant;
			keyIndex = t.keyIndex;
			PK = t.PK;
			NK = t.NK;
			head = t.head;
			frames = t.frames;
			keyFrames = t.keyFrames;
			loop = t.loop;
			keys = t.keys;
			actualState = t.actualState;
		}
	}

	Track::~Track()
	{
		trackDelegate.clear();
	}

	const Track& Track::operator=(const Track& t)
	{
		if(&t != this)
		{
			frameCounter = t.frameCounter;
			frameTime = t.frameTime;
			trackDelegate = t.trackDelegate;
			value = t.value;
			derivative = t.derivative;
			timeDerivative = t.timeDerivative;
			constant = t.constant;
			keyIndex = t.keyIndex;
			PK = t.PK;
			NK = t.NK;
			head = t.head;
			frames = t.frames;
			keyFrames = t.keyFrames;
			loop = t.loop;
			keys = t.keys;
			actualState = t.actualState;
		}
		return *this;
	}

	bool Track::operator==(const Track& t) const
	{
		if( head == t.head &&
			frames == t.frames &&
			loop == t.loop &&
			keys == t.keys &&
			keyFrames == t.keyFrames &&
			PK == t.PK &&  NK == t.NK &&
			keyIndex == t.keyIndex &&
			value == t.value &&
			derivative == t.derivative &&
			timeDerivative == t.timeDerivative &&
			constant == t.constant &&
			frameTime == t.frameTime &&
			frameCounter == t.frameCounter)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Track::operator<(const Track& t)const
	{
		if(keys < t.keys)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Track::init(int frames, int keys, int frameTime, int state, bool constant, float value)
	{
		this->frames = (frames > 0 ? frames : 0);
		this->keys = (keys > 0 ? keys : 0);
		this->frameTime = (frameTime >= 0 ? frameTime : 0);
		actualState = state;		
		this->constant = constant;		

		if (this->constant)
		{
			this->value = value;
			keyFrames.clear();
			this->frames = 1;
			keyFrames.push_back(KeyFrame());
		}
		else
		{
			PK = KeyFrame();
			NK = KeyFrame();
			for (unsigned int i = 0; i < this->keys; i++)
			{
				keyFrames.push_back(KeyFrame());
			}
		}
	}

	void Track::calculateDerivative()
	{

	}

	void Track::applyDerivative()
	{
		float tempValue = 0.0f;
		float tempTime = 0.0f;
		int h = 0;
		time = 0;
		timeDerivative = abs(NK.time - PK.time);
		h = abs(head - PK.time);
		tempTime = h / timeDerivative;
		if(isnan(tempTime) == 0)
		{
			time = tempTime;
		}

		float p0t = 0.0f;
		float p0v = 0.0f;

		float p1t = 0.0f;
		float p1v = 0.0f;

		float p2t = 0.0f;
		float p2v = 0.0f;

		float p3t = 0.0f;
		float p3v = 0.0f;

		if(!constant)
		{
			if(actualState == 0 || actualState == 6)
			{
				if(NK.easingForward == KeyFrame::LINEAR)
				{
					p0t = PK.time;
					p0v = PK.value;
					p1t = NK.time;
					p1v = NK.value;

					tempValue = p0v + (p1v  - p0v) * time;
					if(isnan(tempValue) == 0)
					{
						value = tempValue;
					}
				}
				if(NK.easingForward == KeyFrame::ACCELERATION)
				{
					p0t = PK.time;
					p0v = PK.value;
					p1t = NK.time;
					p1v = PK.value;
					p2t = NK.time;
					p2v = NK.value;
					tempValue = (1-time) * (1-time) * p0v + 2 * time * (1-time) * p1v + time * time * p2v;
					if(isnan(tempValue) == 0)
					{
						value = tempValue;
					}
				}
				if(NK.easingForward == KeyFrame::DECELERATION)
				{
					p0t = PK.time;
					p0v = PK.value;
					p1t = PK.time;
					p1v = NK.value;
					p2t = NK.time;
					p2v = NK.value;
					tempValue = (1-time) * (1-time) * p0v + 2 * time * (1-time) * p1v + time * time * p2v;
					if(isnan(tempValue) == 0)
					{
						value = tempValue;
					}
				}
				if(NK.easingForward == KeyFrame::SMOOTHSTEP)
				{
					p0t = PK.time;
					p0v = PK.value;

					p1t = NK.time;
					p1v = PK.value;

					p2t = PK.time;
					p2v = NK.value;

					p3t = NK.time;
					p3v = NK.value;
					tempValue = p0v * (1-time) * (1-time)  * (1-time) + 3 * p1v * time *  (1-time) * (1-time)  + 3 * p2v * time * time * (1-time) + p3v * time * time * time;
					if(isnan(tempValue) == 0)
					{
						value = tempValue;
					}
				}

				if(NK.easingForward == KeyFrame::DISCRETE)
				{
					value = PK.value;
				}
			}

			if(actualState == 1 || actualState == 7)
			{
				if(NK.easingReverse == KeyFrame::LINEAR)
				{
					p0t = PK.time;
					p0v = PK.value;
					p1t = NK.time;
					p1v = NK.value;
					tempValue = p0v + (p1v  - p0v) * time;
					if(isnan(tempValue) == 0)
					{
						value = tempValue;
					}
				}
				if(NK.easingReverse == KeyFrame::ACCELERATION)
				{
					p0t = PK.time;
					p0v = PK.value;
					p1t = NK.time;
					p1v = PK.value;
					p2t = NK.time;
					p2v = NK.value;
					tempValue = (1-time) * (1-time) * p0v + 2 * time * (1-time) * p1v + time * time * p2v;
					if(isnan(tempValue) == 0)
					{
						value = tempValue;
					}
				}
				if(NK.easingReverse == KeyFrame::DECELERATION)
				{
					p0t = PK.time;
					p0v = PK.value;
					p1t = PK.time;
					p1v = NK.value;
					p2t = NK.time;
					p2v = NK.value;
					tempValue = (1-time) * (1-time) * p0v + 2 * time * (1-time) * p1v + time * time * p2v;
					if(isnan(tempValue) == 0)
					{
						value = tempValue;
					}
				}
				if(NK.easingReverse == KeyFrame::SMOOTHSTEP)
				{
					p0t = PK.time;
					p0v = PK.value;

					p1t = NK.time;
					p1v = PK.value;

					p2t = PK.time;
					p2v = NK.value;

					p3t = NK.time;
					p3v = NK.value;
					tempValue = p0v * (1-time) * (1-time)  * (1-time) + 3 * p1v * time *  (1-time) * (1-time)  + 3 * p2v * time * time * (1-time) + p3v * time * time * time;
					if(isnan(tempValue) == 0)
					{
						value = tempValue;
					}
				}
				if(NK.easingReverse == KeyFrame::DISCRETE)
				{
					value = PK.value;
				}
			}
		}
	}

	void Track::updateEvent()
	{
		if(!constant)
		{
			if(head == NK.time)
			{
				if(NK.keyDelegate.size() != 0)
				{
					vector<KeyFrameDelegate*>::iterator it;

					if(actualState == TrackAction::FORWARD)
					{
						for( it = NK.keyDelegate.begin(); it != NK.keyDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onForward();
							}
						}
					}

					if(actualState == TrackAction::BACKWARD)
					{
						for( it = NK.keyDelegate.begin(); it != NK.keyDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onBackward();
							}
						}
					}

					if(actualState == TrackAction::LOOP_FORWARD)
					{
						for( it = NK.keyDelegate.begin(); it != NK.keyDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onLoopForward();
							}
						}
					}

					if(actualState == TrackAction::LOOP_BACKWARD)
					{
						for( it = NK.keyDelegate.begin(); it != NK.keyDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onLoopBackward();
							}
						}
					}
				}

				if(NK.action.active)
				{
					switch(NK.action.actualState)
					{
						case TrackAction::LOOP_FORWARD:
						{
							if(NK.action.direction == actualState || actualState == TrackAction::STOP)
							actualState = TrackAction::LOOP_FORWARD;
						}
						break;

						case TrackAction::FORWARD:
						{
							if(NK.action.direction == actualState || actualState == TrackAction::STOP)
							actualState = TrackAction::FORWARD;
						}
						break;

						case TrackAction::LOOP_BACKWARD:
						{
							if(NK.action.direction == actualState || actualState == TrackAction::STOP)
							actualState = TrackAction::LOOP_BACKWARD;
						}
						break;

						case TrackAction::BACKWARD:
						{
							if(NK.action.direction == actualState || actualState == TrackAction::STOP)
							actualState = TrackAction::BACKWARD;
						}
						break;

						case TrackAction::PAUSE:
						{
							if(NK.action.pauseCounter == 0)
							{
								NK.action.previousAction = actualState;
							}

							if(NK.action.pauseTime > 0)
							{
								if(NK.action.pauseCounter < NK.action.pauseTime)
								{
									if(actualState == TrackAction::PAUSE )
									{
										NK.action.pauseCounter++;
									}

									if(NK.action.direction == actualState )
									{
										actualState = TrackAction::PAUSE;
										NK.action.pauseCounter++;
									}
								}
								else
								{
									actualState = NK.action.previousAction;
									NK.action.pauseCounter = 0;
								}
							}
						}
						break;

						case TrackAction::PAUSE_FORWARD:
						{
							if(NK.action.pauseCounter < NK.action.pauseTime)
							{
								if(actualState == TrackAction::PAUSE )
								{
									NK.action.pauseCounter++;
								}

								if(NK.action.direction == actualState )
								{
									actualState = TrackAction::PAUSE;
									NK.action.pauseCounter++;
								}
							}
							else
							{
								actualState = TrackAction::FORWARD;
								NK.action.pauseCounter = 0;
							}
						}
						break;

						case TrackAction::PAUSE_BACKWARD:
						{
							if(NK.action.pauseCounter < NK.action.pauseTime)
							{
								if(actualState == TrackAction::PAUSE )
								{
									NK.action.pauseCounter++;
								}

								if(NK.action.direction == actualState )
								{
									actualState = TrackAction::PAUSE;
									NK.action.pauseCounter++;
								}
							}
							else
							{
								actualState = TrackAction::BACKWARD;
								NK.action.pauseCounter = 0;
							}
						}
						break;

						case TrackAction::GO_TO_KEY:
						{
							if(NK.action.direction == actualState)
							{
								goToKey(NK.action.destinationKey);
							}
						}
						break;

						case TrackAction::GO_TO_KEY_FORWARD:
						{
							if(NK.action.direction == actualState)
							{
								goToKeyAndForward(NK.action.destinationKey);
							}
						}
						break;

						case TrackAction::GO_TO_KEY_BACKWARD:
						{
							if(NK.action.direction == actualState)
							{
								goToKeyAndBackward(NK.action.destinationKey);
							}
						}
						break;

						case TrackAction::GO_TO_KEY_STOP:
						{
							if(NK.action.direction == actualState)
							{
								goToKeyAndStop(NK.action.destinationKey);
							}
						}
						break;

						case TrackAction::STOP:
						{
							if(NK.action.direction == actualState)
							{
								actualState = TrackAction::STOP;
							}
						}
						break;

						default:
						break;
					}
				}
			}
		}
	}

	void Track::update()
	{
		applyDerivative();
		updateEvent();
		unsigned int previousState = actualState;
		float previousValue = value;
		vector<TrackDelegate*>::iterator it;
		float headPosition = head;

		if(!constant)
		{
			switch(actualState)
			{
				case TrackAction::FORWARD:
				{
					loop = false;
					forward();

					//On forward event//
					if(trackDelegate.size() != 0)
					{
						for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onForward();
							}
						}
					}
				}
				break;

				case TrackAction::BACKWARD:
				{
					loop = false;
					backward();

					//On reverse event//
					if(trackDelegate.size() != 0)
					{
						for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onBackward();
							}
						}
					}
				}
				break;

				case TrackAction::PAUSE:
				{
					loop = false;
					pause();

					//On pause event//
					if(trackDelegate.size() != 0)
					{
						for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onPause();
							}
						}
					}
				}
				break;

				case TrackAction::STOP:
				{
					loop = false;
					stop();

					//On stop event//
					if(trackDelegate.size() != 0)
					{
						for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onStop();
							}
						}
					}
				}
				break;

				case TrackAction::LOOP_FORWARD:
				{
					loop = true;
					forward();

					//On loop forward event//
					if(trackDelegate.size() != 0)
					{
						for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onLoopForward();
							}
						}
					}
				}
				break;

				case TrackAction::LOOP_BACKWARD:
				{
					loop = true;
					backward();

					//On loop reverse event//
					if(trackDelegate.size() != 0)
					{
						for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
						{
							if((*it) != NULL)
							{
								(*it)->onLoopBackward();
							}
						}
					}
				}
				break;

				default:
				break;
			}
		}


		//On changed state event//
		if(actualState != previousState)
		{
			if(trackDelegate.size() != 0)
			{
				for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
				{
					if((*it) != NULL)
					{
						(*it)->onStateChanged(actualState);
					}
				}
			}
		}

		//On changed direction event//
		if(previousState == TrackAction::FORWARD && actualState == TrackAction::BACKWARD)
		{
			if(trackDelegate.size() != 0)
			{
				for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
				{
					if((*it) != NULL)
					{
						(*it)->onDirectionChanged(actualState);
					}
				}
			}
		}

		//On changed direction event//
		if(previousState == TrackAction::BACKWARD && actualState == TrackAction::FORWARD)
		{
			if(trackDelegate.size() != 0)
			{
				for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
				{
					if((*it) != NULL)
					{
						(*it)->onDirectionChanged(actualState);
					}
				}
			}
		}

		//On first frame event//
		if(head == 0)
		{
			if(trackDelegate.size() != 0)
			{
				for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
				{
					if((*it) != NULL)
					{
						(*it)->onFirstFrame();
					}
				}
			}
		}

		//On last frame event//
		if(head == frames - 1)
		{
			if(trackDelegate.size() != 0)
			{
				for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
				{
					if((*it) != NULL)
					{
						(*it)->onLastFrame();
					}
				}
			}
		}

			//On value changed event//
			if(previousValue != value)
			{
				if(trackDelegate.size() != 0)
				{
					for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
					{
						if((*it) != NULL)
						{
							(*it)->onValueChanged(value);
						}
					}
				}
			}

			//On value changed to zero event//
			if(value <= 0.0f)
			{
				if(trackDelegate.size() != 0)
				{
					for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
					{
						if((*it) != NULL)
						{
							(*it)->onValueChangedToZero();
						}
					}
				}
			}

			//On value changed to one event//
			if(value >= 1.0f)
			{
				if(trackDelegate.size() != 0)
				{
					for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
					{
						if((*it) != NULL)
						{
							(*it)->onValueChangedToOne();
						}
					}
				}
			}

			//On key frame event
			if(head == NK.time)
			{
				if(trackDelegate.size() != 0)
				{
					for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
					{
						if((*it) != NULL)
						{
							(*it)->onKeyFrame(head);
						}
					}
				}
			}

			//On head position changed event//
			if(headPosition != head)
			{
				if(trackDelegate.size() != 0)
				{
					for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
					{
						if((*it) != NULL)
						{
							(*it)->onHeadPositionChanged(head);
						}
					}
				}
			}

			//On head position changed forward//
			if(headPosition < head)
			{
				if(trackDelegate.size() != 0)
				{
					for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
					{
						if((*it) != NULL)
						{
							(*it)->onHeadPositionChangedForward(head);
						}
					}
				}
			}

			//On head position changed backward//
			if(headPosition > head)
			{
				if(trackDelegate.size() != 0)
				{
					for (it = trackDelegate.begin(); it != trackDelegate.end(); it++)
					{
						if((*it) != NULL)
						{
							(*it)->onHeadPositionChangedBackward(head);
						}
					}
				}
			}
	}

	void Track::forward()
	{
		if(head < frames - 1)
		{
			if(head == NK.time)
			{
				if(keyIndex >= 0 && keyIndex <= keys - 1)
				{
					//Set the previous key frame//
					PK = keyFrames.at(keyIndex);

					if(keyIndex < keys - 1)
					{
						keyIndex++;
					}

					//Set the next key frame//
					NK = keyFrames.at(keyIndex);
				}
			}

			if(frameCounter > frameTime)
			{
				head++;
				frameCounter = 0;
			}
			else
			{
				frameCounter++;
			}
		}
		else
		{
			if(loop)
			{
				goToFirstKey();
				actualState = TrackAction::LOOP_FORWARD;
			}
		}
	}

	void Track::backward()
	{
		if(head > 0)
		{
			if(head == NK.time)
			{
				if(keyIndex >= 0 && keyIndex <= keys - 1)
				{
					//Set previous key frame//
					PK = keyFrames.at(keyIndex);

					if(keyIndex > 0)
					{
						keyIndex--;
					}

					//Set next key frame//
					NK = keyFrames.at(keyIndex);
				}
			}

			if(frameCounter > frameTime)
			{
				head--;
				frameCounter = 0;
			}
			else
			{
				frameCounter++;
			}
		}
		else
		{
			if(loop)
			{
				goToLastKey();
				actualState = TrackAction::LOOP_BACKWARD;
			}
		}
	}

	void Track::goToKey( int key)
	{
		if(key >=0 && key <= keys - 1)
		{
			keyIndex = key;
			NK = keyFrames.at(keyIndex);
			head = NK.time;
		}
	}

	void Track::goToKeyAndForward( int key)
	{
		if(key >=0 && key <= keys - 1)
		{
			keyIndex = key;
			NK = keyFrames.at(keyIndex);
			head = NK.time;
			actualState = TrackAction::FORWARD;
		}
	}

	void Track::goToKeyAndBackward( int key)
	{
		if(key >=0 && key <= keys - 1)
		{
			keyIndex = key;
			NK = keyFrames.at(keyIndex);
			head = NK.time;
			actualState = TrackAction::BACKWARD;
		}
	}

	void Track::goToKeyAndStop( int key)
	{
		if(key >=0 && key <= keys - 1)
		{
			keyIndex = key;
			NK = keyFrames.at(keyIndex);
			head = NK.time;
			actualState = TrackAction::STOP;
		}
	}

	void Track::pause()
	{

	}

	void Track::stop()
	{


	}

	void Track::goToFirstKey()
	{
		keyIndex = 0;
		head = 0;
		PK = keyFrames.at(0);
		NK = keyFrames.at(0);
	}

	void Track::goToFirstKeyAndForward()
	{
		keyIndex = 0;
		head = 0;
		PK = keyFrames.at(0);
		NK = keyFrames.at(0);
		actualState = TrackAction::FORWARD;
	}

	void Track::goToFirstKeyAndBackward()
	{
		keyIndex = 0;
		head = 0;
		PK = keyFrames.at(0);
		NK = keyFrames.at(0);
		actualState = TrackAction::BACKWARD;
	}

	void Track::goToFirstKeyAndStop()
	{
		keyIndex = 0;
		head = 0;
		PK = keyFrames.at(0);
		NK = keyFrames.at(0);
		actualState = TrackAction::STOP;
	}

	void Track::goToLastKey()
	{
		keyIndex = keys - 1;
		head = frames - 1;
		NK = keyFrames.at(keyIndex);
	}

	void Track::goToLastKeyAndForward()
	{
		keyIndex = keys - 1;
		head = frames - 1;
		NK = keyFrames.at(keyIndex);
		actualState = TrackAction::FORWARD;
	}

	void Track::goToLastKeyAndBackward()
	{
		keyIndex = keys - 1;
		head = frames - 1;
		NK = keyFrames.at(keyIndex);
		actualState = TrackAction::BACKWARD;
	}

	void Track::goToLastKeyAndStop()
	{
		keyIndex = keys - 1;
		head = frames - 1;
		NK = keyFrames.at(keyIndex);
		actualState = TrackAction::STOP;
	}

	void Track::print() const
	{

	}


