#pragma once
#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

#include "ScreenObject.h"
#include "Bullet.h"
#include "SolutionPossibility.h"
#include "NumberEaters.h"
#include "RowFlyers.h"
#include "ColumnFlyers.h"
#include "Bullet.h"
#include "Player.h"

class CollisionManager
{
public:
	void static collesion(Bullet * obj1, ScreenObject * obj2);
	void static collesion(Creature * obj1, ScreenObject * obj2);
	void static collesion(Player * obj1, ScreenObject * obj2);
	void static collesionWithBulletMain(Bullet * obj1, ScreenObject * obj2);
	void static collesionWithPlayer(ScreenObject * obj1, ScreenObject * obj2);
	void static collesionWithPlayerMain(ScreenObject * obj1, ScreenObject * obj2);
	void static collesionWithNumberEaters(ScreenObject * obj1, ScreenObject * obj2);
	void static collesionWithNumberEatersMain(NumberEaters * obj1, ScreenObject * obj2);

};

#endif