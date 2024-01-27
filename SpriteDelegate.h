#include "stdafx.h"

#ifndef SPRITEDELEGATE_H
#define SPRITEDELEGATE_H

class SpriteDelegate
{
	public:
		__declspec(dllexport) 		  SpriteDelegate() {};
		__declspec(dllexport) virtual ~SpriteDelegate() {};
		
		__declspec(dllexport) virtual void onCreate() {}
		__declspec(dllexport) virtual void onDestroy() {};
		

};
#endif // !SPRITEDELEGATE_H
