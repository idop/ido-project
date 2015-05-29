//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Bullet.cpp
// -------------
// This Bullet class is resposible for the Draw and Clear options of the object.
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-05-03
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Bullet.h"
#include "io_utils.h"

using namespace std;

void Bullet::Draw()const
{
	gotoxy(GetPosition().GetX(), GetPosition().GetY());
	cout << bullet;
}

 void Bullet::Move(const Point & p){
	Clear();
	SetPosition(p);
	Draw();
} // moves the player to a new position p according to this direction
