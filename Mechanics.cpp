
#include "stdafx.h"

Mechanics::Mechanics()
{
	mass = 0.0f;
	direction = vec3();
	position = vec3();
	acceleration = vec3();
	maxSpeed = vec3();
	speed = vec3();
	inertia = vec3();
	friction = vec3();
	momentum = vec3();
	gravity = vec3();
}

Mechanics::Mechanics(const Mechanics &m)
{
	if (&m != this)
	{
		mass = m.mass;
		direction = m.direction;
		position = m.position;
		acceleration = m.acceleration;
		maxSpeed = m.maxSpeed;
		speed = m.speed;
		inertia = m.inertia;
		friction = m.friction;
		momentum = m.momentum;
		gravity = m.gravity;
	}
}

Mechanics::~Mechanics()
{

}

const Mechanics &Mechanics::operator=(const Mechanics &m)
{
	if (&m != this)
	{
		mass = m.mass;
		direction = m.direction;
		position = m.position;
		acceleration = m.acceleration;
		speed = m.speed;
		maxSpeed = m.maxSpeed;
		inertia = m.inertia;
		friction = m.friction;
		momentum = m.momentum;
		gravity = m.gravity;
	}
	return *this;
}

bool Mechanics::operator==(const Mechanics &m) const
{
	if(
		mass == m.mass &&
		direction == m.direction &&
		position == m.position &&
		acceleration == m.acceleration &&
		speed == m.speed &&
		maxSpeed == m.maxSpeed &&
		inertia == m.inertia &&
		friction == m.friction &&
		momentum == m.momentum &&
		gravity == m.gravity	)
	{
		return true;
	}
	else
		return false;
}

bool Mechanics::operator<(const Mechanics &m) const
{
	return false;
}

bool Mechanics::operator>(const Mechanics &m) const
{
	return false;
}

bool Mechanics::operator*(const Mechanics &m) const
{
	return false;
}

void Mechanics::update()
{
}

void Mechanics::print() const
{
	cout << "Mass = " << mass << endl;
	cout << "Direction = " << "[" << direction.x << "," << direction.y << "," << direction.z << "]" << endl;
	cout << "Position = "<< "[" << position.x << "," << position.y << "," << position.z << "]"<<endl;
	cout << "Acceleration = "<< "[" << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << "]"<<endl;
	cout << "Speed = "<< "[" << speed.x << ", " << speed.y << ", " << speed.z << "]"<<endl;
	cout << "Max Speed = " << "[" << maxSpeed.x << ", " << maxSpeed.y << ", " << maxSpeed.z << "]" << endl;
	cout << "Inertia = "<< "[" << inertia.x << ", " << inertia.y << ", " << inertia.z << "]"<<endl;
	cout << "Friction = "<< "[" << friction.x << ", " << friction.y << ", " << friction.z << "]"<<endl;
	cout << "Momentum = "<< "[" << momentum.x << ", " << momentum.y << ", " << momentum.z << "]"<<endl;
	cout << "Gravity = "<< "[" << gravity.x << ", " << gravity.y << ", " << gravity.z << "]"<<endl;
}
