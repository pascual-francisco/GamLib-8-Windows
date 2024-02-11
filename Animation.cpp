#include "stdafx.h"

namespace animation
{
	animation::Animation::Animation()
	{
		init();
	}

	Animation::Animation(GLint firstframe, GLint lastframe, GLint actualframe, GLfloat frametime, GLuint actualstate)
	{			
		init(firstframe, lastframe, actualframe, frametime, actualstate);
	}

	Animation::~Animation()
	{

	}

	Animation::Animation(const Animation& object)
	{
		if (&object != this)
		{
			firstFrame = object.firstFrame;
			lastFrame = object.lastFrame;
			actualFrame = object.actualFrame;
			frameCounter = object.frameCounter;
			frameTime = object.frameTime;
			loopCounter = object.loopCounter;
			loop = object.loop;
			keyFrames = object.keyFrames;
		}
	}

	void Animation::init(GLint firstframe, GLint lastframe, GLint actualframe, GLfloat frametime, GLuint actualstate)
	{
		frameCounter = 0;
		loop = true;
		loopCounter = 0;

		if (firstframe >= 0)
		{
			firstFrame = firstframe;
		}
		else
		{
			firstFrame = 0;
		}

		if (lastframe >= 0)
		{
			lastFrame = lastframe;
		}
		else
		{
			lastFrame = 0;
		}

		if (actualframe >= firstFrame && actualframe <= lastFrame)
		{
			actualFrame = actualframe;
		}
		else
		{
			actualFrame = 0;
		}

		if (frametime >= 0)
		{
			frameTime = frametime;
		}
		else
		{
			frameTime = 0;
		}

		if (actualstate >= AnimationStates::FORWARD || actualstate <= AnimationStates::STOP)
		{
			animationState = actualstate;
		}
		else
		{
			animationState = AnimationStates::FORWARD;
		}

		keyFrames = vector < GLuint >(lastFrame + 1);
	}

	void Animation::update()
	{
		if (lastFrame > firstFrame)
		{
			if (animationState == AnimationStates::FORWARD)
			{
				if (frameCounter < frameTime)
				{
					frameCounter++;
				}
				else
				{
					if (actualFrame < lastFrame)
					{
						actualFrame++;
					}
					frameCounter = 0;
				}
			}

			if (animationState == AnimationStates::BACKWARD)
			{
				if (frameCounter < frameTime)
				{
					frameCounter++;
				}
				else
				{
					if (actualFrame > firstFrame)
					{
						actualFrame--;
					}
					frameCounter = 0;
				}
			}

			if (animationState == AnimationStates::LOOP_FORWARD)
			{
				if (frameCounter < frameTime)
				{
					frameCounter++;
				}
				else
				{
					if (actualFrame < lastFrame)
					{
						actualFrame++;
					}
					else
					{
						actualFrame = firstFrame;
						loopCounter++;
					}
					frameCounter = 0;
				}
			}

			if (animationState == AnimationStates::LOOP_BACKWARD)
			{
				if (frameCounter < frameTime)
				{
					frameCounter++;
				}
				else
				{
					if (actualFrame > firstFrame)
					{
						actualFrame--;
					}
					else
					{
						actualFrame = lastFrame;
						loopCounter++;
					}
					frameCounter = 0;
				}
			}

			if (animationState == AnimationStates::PAUSE)
			{

			}

			if (animationState == AnimationStates::STOP)
			{
				frameCounter = 0;
				actualFrame = firstFrame;
			}
		}
	}

	const Animation& Animation::operator=(const Animation& object)
	{
		if (&object != this)
		{
			active = object.active;
			objectID = object.objectID;
			name = object.name;
			animationState = object.animationState;
			firstFrame = object.firstFrame;
			lastFrame = object.lastFrame;
			actualFrame = object.actualFrame;
			frameCounter = object.frameCounter;
			frameTime = object.frameTime;
			loopCounter = object.loopCounter;
			loop = object.loop;
			keyFrames = object.keyFrames;
		}
		return *this;
	}

	bool Animation::operator==(const Animation& a) const
	{
		if (&a != this)
		{
			if (
				active == a.active &&
				objectID == a.objectID &&
				name == a.name &&
				animationState == a.animationState &&
				firstFrame == a.firstFrame &&
				lastFrame == a.lastFrame &&
				actualFrame == a.actualFrame &&
				frameCounter == a.frameCounter &&
				frameTime == a.frameTime &&
				loopCounter == a.loopCounter &&
				loop == a.loop &&
				keyFrames == a.keyFrames
				)
				return true;
			else
				return false;
		}
		else return false;
	}

	bool Animation:: operator<(const Animation& a) const
	{
		if (lastFrame < a.lastFrame)
			return true;

		else
			return false;
	}

	bool Animation::operator<(uint n) const
	{
		if (lastFrame < n)
			return true;

		else
			return false;
	}

	bool Animation::operator>(const Animation& a) const
	{
		if (lastFrame > a.lastFrame)
			return true;

		else
			return false;
	}

	bool Animation::operator>(uint n) const
	{
		if (lastFrame > n)
			return true;

		else
			return false;
	}

	Animation& Animation::operator-(const Animation& obj) const
	{
		// TODO: insert return statement here
	}

	void Animation::operator-(uint n)
	{
		if (keyFrames.size() - 1 > n)
		{
			for (uint i = 0; i < n; i++)
			{
				keyFrames.pop_back();
				lastFrame--;
			}
		}
	}

	void Animation::operator--()
	{
		if (!keyFrames.empty())
		{
			keyFrames.pop_back();
			lastFrame--;
		}
	}

	Animation& Animation::operator+(const Animation& obj) const
	{		
		Animation A(*this);

		for (uint i = 0; i < obj.keyFrames.size(); i++)
			A.keyFrames.push_back(obj.keyFrames[i]);			
	
		A.lastFrame = lastFrame + obj.lastFrame;
		return A;
	}

	void Animation::operator+(uint n)
	{				
		keyFrames.push_back(n);
		lastFrame++;		
		actualFrame = 0;
	}

	void Animation::operator++()
	{
		keyFrames.push_back(0);
		lastFrame++;
		actualFrame = 0;
	}
		
	void Animation::operator>>(uint n)
	{
		if (keyFrames.size() - 1 > n)
		{		
			actualFrame = n;
			animationState = Animation::FORWARD;
		}
	}
	
	void Animation::operator<<(uint n)
	{
		if (keyFrames.size() - 1 > n)
		{
			actualFrame = n;
			animationState = Animation::BACKWARD;
		}
	}

	Animation& Animation::operator[](uint i) const
	{		
		Animation A(*this);

		if (keyFrames.size() - 1 > i)
		{
			Animation A(*this);								
			
			if (keyFrames.size() - 1 > n)
			{
				for (uint i = 0; i < n; i++)
				{
					keyFrames.pop_back();
					lastFrame--;
				}
			
			A - i;						
			return A;
		}
		else
		{
			return A;
		}
	}

	int Animation::operator[](int i) const
	{
		if (keyFrames.size() - 1 > i)
		{
			return keyFrames[i];
		}
		else
		{
			return -1;
		}
	}

	Animation& Animation::operator()(void* fun_ptr, uint x) const
	{
		// TODO: insert return statement here
	}

	Animation& Animation::operator()(uint x, uint y, uint z) const
	{
		// TODO: insert return statement here
	}

	void Animation::print() const
	{		
		cout << "Animation Data: " << endl;
		cout << "Object ID = " << objectID << endl;
		cout << "Name = " << name << endl;
		cout << "Actual State = " << animationState << endl;
		cout << "Actual Frame = " << actualFrame << endl;
		cout << "First Frame = " << firstFrame << endl;
		cout << "Last Frame = " << lastFrame << endl;
		cout << "Frame Time = " << frameTime << endl;
		cout << "Loop = " << loop << endl;
		cout << "Loop Counter = " << loopCounter << endl;
		cout << "Frame Counter = " << frameCounter << endl;
		cout << "Animation Data: " << endl;
		cout << "Frame Data: " << endl;

		if (!keyFrames.empty())
		{
			for (int i = 0; i < lastFrame; i++)
			{
				cout << "[" << i << "] = " << keyFrames[i] << endl;
			}
		}
		else
		{
			cout << "Empty" << endl;
		}	
	}
}