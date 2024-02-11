#include "stdafx.h"

namespace object
{
	#ifndef OBJECT_H
	#define OBJECT_H

	class Object
	{
		public:		
		bool	active;
		string	name;
		uint	objectID;

		__declspec(dllexport) Object();
		__declspec(dllexport) Object(const Object& obj);
		__declspec(dllexport) ~Object();

		__declspec(dllexport) virtual void init();
		__declspec(dllexport) virtual void update() = 0;
		__declspec(dllexport) virtual void print() const = 0;

		__declspec(dllexport) virtual const Object& operator=(const Object& obj);		
		__declspec(dllexport) virtual bool operator==(const Object& obj) const;
		__declspec(dllexport) virtual bool operator<(const Object& obj) const;
		__declspec(dllexport) virtual bool operator<(uint n) const;
		__declspec(dllexport) virtual bool operator>(const Object& obj) const;		
		__declspec(dllexport) virtual bool operator>(uint n) const;
		__declspec(dllexport) virtual Object& operator-(const Object& obj) const;		
		__declspec(dllexport) virtual void operator-(uint n);
		__declspec(dllexport) virtual void operator--();
		__declspec(dllexport) virtual Object& operator+(const Object& obj) const;		
		__declspec(dllexport) virtual void operator+(uint n);
		__declspec(dllexport) virtual void operator++();
		__declspec(dllexport) virtual Object& operator/(const Object& obj) const;
		__declspec(dllexport) virtual void operator/(uint d);
		__declspec(dllexport) virtual Object& operator*(const Object& obj) const;
		__declspec(dllexport) virtual void operator*(int m);
		__declspec(dllexport) virtual Object& operator>>(const Object& obj) const;				
		__declspec(dllexport) virtual void operator>>(uint n);
		__declspec(dllexport) virtual Object& operator<<(const Object& obj) const;				
		__declspec(dllexport) virtual void operator<<(uint n);
		__declspec(dllexport) virtual Object& operator[](uint i) const;
		__declspec(dllexport) virtual int operator[](int i) const;
		__declspec(dllexport) virtual Object& operator()(void* fun_ptr, uint x) const;				
		__declspec(dllexport) virtual Object& operator()(uint x, uint y, uint z) const;		
	};
	#endif


}
