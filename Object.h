#include "stdafx.h"

namespace Objects
{

	#ifndef OBJECT_H
	#define OBJECT_H

	class Object
	{
	public:
		GLuint objectID;
		string name;

		__declspec(dllexport) Object();
		__declspec(dllexport) Object(const Object& obj);
		__declspec(dllexport) ~Object();

		__declspec(dllexport) virtual void init() = 0;
		__declspec(dllexport) virtual void update() = 0;
		__declspec(dllexport) virtual void print() const = 0;

		__declspec(dllexport) virtual const Object& operator=(const Object& obj);
		__declspec(dllexport) virtual bool operator==(const Object& obj) const;
		__declspec(dllexport) virtual bool operator<(const Object& obj) const;
		__declspec(dllexport) virtual bool operator>(const Object& obj) const;
		__declspec(dllexport) virtual Object& operator-(const Object& obj) const;
		__declspec(dllexport) virtual void operator--() const;
		__declspec(dllexport) virtual Object& operator+(const Object& obj) const;
		__declspec(dllexport) virtual void operator++() const;
		__declspec(dllexport) virtual Object& operator/(const Object& obj) const;
		__declspec(dllexport) virtual Object& operator*(const Object& obj) const;
		__declspec(dllexport) virtual Object& operator>>(const Object& obj) const;
		__declspec(dllexport) virtual Object& operator<<(const Object& obj) const;

	};
	#endif
}
