#pragma once
#include "Creature.h"


class NumberEaters :
	public Creature
{
	char sign = '%';

public:

	NumberEaters(const Point & p, const Direction::value & d) : Creature(p, d){};
	virtual ~NumberEaters();

	virtual void Draw()const override; //inherited  from the Screenobject class draws the player
	virtual void Collesion() override{ };
	virtual void Move(const Point & p) override;

};

