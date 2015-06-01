#include "CollisionManager.h"


void CollisionManager::collesion(Bullet * obj1, ScreenObject * obj2)
{
	collesionWithBulletMain(obj1, obj2);
}

void CollisionManager::collesion(Player* obj1, ScreenObject* obj2)
{
	if (dynamic_cast<NumberEaters*>(obj2) != nullptr)
	{
		obj2->destroy();
		obj2->Clear();
		return;
	}
	if (dynamic_cast<Bullet*>(obj2) != nullptr)
	{
		collesionWithBulletMain(dynamic_cast<Bullet*>(obj2), obj1);
	}
}

void CollisionManager::collesion(Creature* obj1, ScreenObject* obj2)
{
	if (dynamic_cast<NumberEaters*>(obj1) != nullptr)
	{
		collesionWithNumberEatersMain(dynamic_cast<NumberEaters*>(obj1), obj2);
		return;
	}
	
	if (dynamic_cast<RowFlyers*>(obj2) == nullptr)
	{
		obj2->destroy();
		obj2->Clear();
		return;
	}
}

void CollisionManager::collesionWithPlayerMain(ScreenObject * obj1, ScreenObject * obj2)
{
	if (dynamic_cast<Player*>(obj2) == nullptr)
	{
		if (dynamic_cast<NumberEaters*>(obj2) != nullptr)
		{
			Player * tmpPlayer = dynamic_cast<Player*>(obj1);
			NumberEaters * tmpNumberEaters = dynamic_cast<NumberEaters*>(obj2);
			tmpPlayer->destroy();
			tmpPlayer->Clear();
			tmpNumberEaters->destroy();
			tmpNumberEaters->Clear();
		} else
		{
			Player * tmpPlayer = dynamic_cast<Player*>(obj1);
			tmpPlayer->destroy();
			tmpPlayer->Clear();
		}
	}
}
void CollisionManager::collesionWithPlayer(ScreenObject * obj1, ScreenObject * obj2)
{
	if (dynamic_cast<Player*>(obj1) != nullptr)
	{
		collesionWithPlayerMain(obj1, obj2);
	}
	else
	{
		collesionWithPlayerMain(obj2, obj1);
	}
}

void CollisionManager::collesionWithNumberEaters(ScreenObject * obj1, ScreenObject * obj2)
{
	if (dynamic_cast<NumberEaters*>(obj1) != nullptr)
	{
		collesionWithNumberEatersMain(dynamic_cast<NumberEaters*>(obj1), obj2);
	} else
	{
		collesionWithNumberEatersMain(dynamic_cast<NumberEaters*>(obj2), obj1);
	}
}

void CollisionManager::collesionWithBulletMain(Bullet * obj1, ScreenObject * obj2)
{
	obj1->destroy();

	if (dynamic_cast<Player*>(obj2) != nullptr || dynamic_cast<NumberEaters*>(obj2) != nullptr)
	{
		obj2->destroy();
	}
	
}


void CollisionManager::collesionWithNumberEatersMain(NumberEaters * obj1, ScreenObject * obj2)
{
	obj1->destroy();
	if (dynamic_cast<NumberEaters*>(obj2) != nullptr)
	{
		NumberEaters * tmpNumberEaters = dynamic_cast<NumberEaters*>(obj2);
		tmpNumberEaters->destroy();
		tmpNumberEaters->Clear();
	}
}