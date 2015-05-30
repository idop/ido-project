//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MovingScreenObject.cpp
// -------------
// TODO ADD SHIT HERE
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-05-03
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "MovingScreenObject.h" 

void MovingScreenObject::Move(const Point& p)
{
	Clear();
	SetPosition(p);
	Draw();
}

void MovingScreenObject::Draw() const
{
	gotoxy(GetPosition().GetX(), GetPosition().GetY());
	cout << this->sign;
}