#pragma once
#include "Creature.h"
class ColumnFlyers :
	public Creature
{
public:
	ColumnFlyers(const Point & p, const Direction::value & d) : Creature(p, d, '$'){};
	virtual ~ColumnFlyers();

	virtual void Draw()const override; //inherited  from the Screenobject class draws the player
	virtual void Collesion() override{ };
	virtual void Move(const Point & p) override;


};