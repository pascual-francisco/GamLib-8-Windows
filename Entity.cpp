#include "Entity.h"

namespace object
{

	Entity::Entity()
	{
		entityID = 0;
		active = true;
		name = "Entity";
		mechanics = Mechanics();
	};

	Entity::~Entity()
	{

	}

	Entity::Entity(const Entity& e)
	{
		active = e.active;
		entityID = e.entityID;
		name = e.name;
		mechanics = e.mechanics;
		sprite = e.sprite;
		tracks = e.tracks;

	}

	const Entity& Entity::operator=(const Entity& e)
	{
		if (&e != this)
		{
			active = e.active;
			entityID = e.entityID;
			name = e.name;
			mechanics = e.mechanics;
			sprite = e.sprite;
			tracks = e.tracks;

		}
		return *this;
	}
	bool Entity::operator==(const Entity& e) const
	{
		if (
			active == e.active &&
			entityID == e.entityID &&
			name == e.name &&
			mechanics == e.mechanics &&
			sprite == e.sprite &&
			tracks == e.tracks

			)
			return true;
		else
			return false;
	}
	bool Entity::operator<(const Entity& e) const
	{
		if (sprite.size() < e.sprite.size())
			return true;
		else
			return false;
	}
	bool Entity::operator>(const Entity& e) const
	{
		if (sprite.size() > e.sprite.size())
			return true;
		else
			return false;
	}

	void Entity::update()
	{

	}

	void Entity::print() const
	{
		cout << "******************************************************************************************************************************************************************************" << endl;
		cout << "Entity Info: " << endl;
		cout << "Entity ID: " << entityID << endl;

		mechanics.print();

		if (sprite.size() > 0)
		{
			for (uint i = 0; i < sprite.size() - 1; i++)
			{
				if (sprite[i] != NULL)
				{
					cout << "Sprite [" << i << "]" << endl;
					sprite[i]->print();
				}
			}
			cout << "-----------------------------" << endl;
		}
		else
		{
			cout << "Sprite is empty" << endl;
			cout << "-----------------------------" << endl;
		}


		cout << "Entity Info: " << endl;
		cout << "******************************************************************************************************************************************************************************" << endl;
	}
}