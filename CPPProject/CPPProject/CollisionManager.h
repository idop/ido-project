//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CollisionManager.h
// -------------
// This class will handle most of the collisions in the game, between two objects
// With Dynamic casting the process will decide what object were send to him, and what actions needs to be taken.
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-05-25
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
	//General or more specific methods for managing collesions between two objects.
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