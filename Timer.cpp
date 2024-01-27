#include "stdafx.h"

	Timer::Timer(unsigned int fr)
	{
		frameRate = (fr>0?fr:0);
		actualFrame = 0;
		memset(&inTime, 0,sizeof(long));
		memset(&outTime, 0, sizeof(long));
		memset(&frameTime, 0, sizeof(long));
		memset(&frequency, 0, sizeof(long));
		QueryPerformanceFrequency(&frequency);
	}

	Timer::~Timer()
	{

	}

	void Timer::update()
	{
		QueryPerformanceCounter(&outTime);

		if(outTime.QuadPart > inTime.QuadPart)
		{
			frameTime.QuadPart += (outTime.QuadPart - inTime.QuadPart) / frequency.QuadPart;
		}

		if(float(frameTime.QuadPart) >= (1/frameRate))
		{
			memset(&frameTime, 0, sizeof(long));
			memset(&inTime, 0, sizeof(long));
			memset(&outTime, 0 ,sizeof(long));

			if(actualFrame < frameRate)
			{
				actualFrame++;
			}
			else
			{
				actualFrame = 0;
			}

			vector<TimerDelegate*>::iterator it;
			if(timerDelegate.size() > 0)
			{
				for(it = timerDelegate.begin(); it !=  timerDelegate.end(); it++)
				{
					if((*it)!=NULL)
					{
						(*it)->onTick();
					}
				}
			}
		}
		QueryPerformanceCounter(&inTime);
	}


