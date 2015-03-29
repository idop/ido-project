#ifndef _METH_GAME_H_
#define _METH_GAME_H_


#include <list>
#include "ISpecificGame.h"

class TheMathGame : public ISpecificGame
{
public:
	virtual bool isLevelDone()const{ return false; }
	virtual bool hasNextLevel()const{ return true; }
	virtual void startLevel(){}
	virtual void doIteration(const list<char>& keyHits){}
	virtual void doSubIteration(){}
};

#endif