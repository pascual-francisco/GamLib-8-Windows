#include "stdafx.h"

namespace object
{

#ifndef ENTITYDELEGATE_H
#define ENTITYDELEGATE_H

	class EntityDelegate
	{
	public:
		__declspec(dllexport) 	  EntityDelegate() {}
		__declspec(dllexport) virtual ~EntityDelegate() {}

		__declspec(dllexport) virtual void onCreate() {}
		__declspec(dllexport) virtual void onDestroy() {}

	};
#endif // !ENTITYDELEGATE_H
}