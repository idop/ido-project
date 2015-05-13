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
	gotoxy(position.getX(), position.getY());
	cout << bullet;
}

void Bullet::Clear()const
{
	gotoxy(position.getX(), position.getY());
	cout << ' ';
}