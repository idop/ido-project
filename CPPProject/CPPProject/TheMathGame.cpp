//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// TheMathGame.cpp
// -------------
// This class  will manage the game, all iterations and start / end / restart of levels
// it will also manage the movment of the players around the screen
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "TheMathGame.h"
#include "io_utils.h"
#include "SolutionPossibility.h"
#include "CollisionManager.h"

bool TheMathGame::hasNextLevel() const
{
	return (currentLevel < maxLevel);
}

void TheMathGame::startLevel(unsigned int level)
{
	/* 
	 * each Start level the function will 
	 * initiallzie player1 and player2 to thier defualt values
	 * and put the players in the default places on screen
	 */

	clear_screen();
	levelDone = false;
	currentLevel = level;
	setTextColor(GetColorForText());
	currentTurn = 0;
	equation1.Init(currentLevel);
	equation2.Init(currentLevel);
	DrawEquations();
	player1.SetToStart(P1_DEFULT_POSITION, P1_DEFULT_DIRECTION);
	player1.Draw();
	player2.SetToStart(P2_DEFULT_POSITION, P2_DEFULT_DIRECTION);
	player2.Draw();
	player1.ResetNumberOfBullets();
	player2.ResetNumberOfBullets();
	bulletList.clear();
	PrintScores();

	if (currentScreen != nullptr)
	{
		delete currentScreen;
	}

	currentScreen = new Screen;
	currentScreen->SetPositionForScreenObject(&player1);
	currentScreen->SetPositionForScreenObject(&player2);
	initCreatureList(currentScreen);
}

//////////////////////////////////////////////////////////
/// change the index for the creature list!!!!!!!!!!!!!!!
//////////////////////////////////////////////////////////
void TheMathGame::initCreatureList(Screen * currentScreen)
{
	if (!creatureList.empty())
	{
		creatureList.clear();
	}


	addNewCreature(new RowFlyers(Point(30, 23), Direction::RIGHT));
	addNewCreature(new RowFlyers(Point(50, 15), Direction::LEFT));


	addNewCreature(new NumberEaters(Point(10, 19), Direction::LEFT, currentScreen));
	//addNewCreature(new NumberEaters(Point(70, 19), Direction::RIGHT, currentScreen));



	addNewCreature(new  ColumnFlyers(Point(45, 23), Direction::UP));
	addNewCreature(new ColumnFlyers(Point(55, 15), Direction::DOWN));



}
//this function will resume the level after sub mani option continue
void TheMathGame::ResumeLevel()
{
	clear_screen();
	PrintScores();
	DrawEquations();
	currentScreen->DrawScrean();
}

void TheMathGame::doIteration(const list<char>& keyHits)  
{
	//for better game play we reduce the refresh rate of new solution possiblties
	if (currentTurn % 2 == 0)
		currentScreen->CreateNewSolutionPosability(currentLevel);

	if (currentTurn % 200 == 0 && currentTurn != 0)
		AddBulletToPlayers();

	// get keystrokes from keyhist list untill the end of the list or until both players got a valid keystroke
	keyStrokeManager(keyHits); 
	runBulletList();
	runCreatuerList(4);
	//for each player we echeck if he has lives to keep on playing , and manage his movment.
	if (player1.GetNumberOfLives() > 0)
	{
		if (player1.GetNumberOfLives() > 0 && player1.isMarkForDestruction()) // TODO Make 1 function for this
		{
			player1.revive();
			player1.SetDirection(P1_DEFULT_DIRECTION);
			player1.Move(P1_DEFULT_POSITION);
			currentScreen->SetPositionForScreenObject(&player1);
		}

		PlayerMovment(player1, equation1);
	}
		

	if (player2.GetNumberOfLives() > 0)
	{
		if (player2.GetNumberOfLives() > 0 && player2.isMarkForDestruction())
		{
			player2.revive();
			player2.SetDirection(P2_DEFULT_DIRECTION);
			player2.Move(P2_DEFULT_POSITION);
			currentScreen->SetPositionForScreenObject(&player2);
		}

		PlayerMovment(player2, equation2);
	}
		
	
	
	//initialazing the end turn checks
	EndTurn();
}


//this function handles all end of turn events. checks if a player lost all his lives 
//or if the level should end (player solved the equation, all players lost thier lives , the level passed the possible max turn
void TheMathGame::EndTurn()
{
	++currentTurn;

	
	if (player1.GetNumberOfLives() == 0)
		currentScreen->ClearScreenObject(&player1);


	if (player2.GetNumberOfLives() == 0)  // if player2 lost all  of his lives  remove him from the screen
		currentScreen->ClearScreenObject(&player2);
	
	if (player1.IsSolutionFound() || player2.IsSolutionFound()) // one of the players solved the equations
	{
		currentScreen->CleanScreen(); // free memory of all dyemic objects
		delete currentScreen;// free the memory for the screen object
		currentScreen = nullptr;
		levelDone = true;
		clear_screen();
		gotoxy(35, 12);
		cout << "Well Done";
		Sleep(1500); 
	}
	else if (currentTurn >= MAX_TURNS_PER_LEVEL || (player2.GetNumberOfLives() == 0 && player1.GetNumberOfLives() == 0)) // current screen reached its max turns limit
	{
		currentScreen->CleanScreen(); // free memory of all dyemic objects
		delete currentScreen; // free the memory for the screen object
		currentScreen = nullptr;
		levelDone = true;
		clear_screen();
		gotoxy(20, 12);
		cout << "Too bad, better luck in the next level";
		Sleep(1500); 
	}
	PrintScores();
}

void TheMathGame::doSubIteration()
{
	runBulletList();
	runCreatuerList(2);
}

void TheMathGame::runBulletList()
{
	for (list<Bullet*>::const_iterator itr = bulletList.cbegin(), end = bulletList.cend(); itr != end; ++itr)
	{
		Bullet* tempBullet = *itr;
		
		if (!tempBullet->isMarkForDestruction())
		{
			Point toMove = tempBullet->getPointToMove();
			ScreenObject* obj = currentScreen->GetScreenObject(toMove.GetX(), toMove.GetY());
			if (obj == nullptr)
				clearAndMove(*tempBullet, toMove, nullptr);
			else if (dynamic_cast<SolutionPosabilty*>(obj) != nullptr){
				currentScreen->ClearScreenObject(obj);
				currentScreen->ClearScreenObject(tempBullet);
				tempBullet->destroy();
			}
			else
			{
				CollisionManager::collesion(tempBullet, obj);
				if (obj->isMarkForDestruction())
					currentScreen->ClearScreenObject(obj);
				currentScreen->ClearScreenObject(tempBullet);
				tempBullet->destroy();
			}
		}


	}
}


void TheMathGame::runCreatuerList(unsigned int len)
{
	int i = 0;
	for (list<Creature*>::const_iterator itr = creatureList.cbegin(), end = creatureList.cend(); i < len, itr != end;i++, ++itr)
	{
		Creature* tempCreature = *itr;
		if (!tempCreature->isMarkForDestruction())
		{
			Point toMove = tempCreature->getPointToMove();
			ScreenObject* obj = currentScreen->GetScreenObject(toMove.GetX(), toMove.GetY());
			if (obj == nullptr)
				clearAndMove(*tempCreature, toMove, nullptr);
			else if (dynamic_cast<SolutionPosabilty*>(obj) != nullptr){
				currentScreen->ClearScreenObject(obj);
				if(tempCreature->isMarkForDestruction())
					currentScreen->ClearScreenObject(tempCreature);
			}
			else
			{
				CollisionManager::collesion(tempCreature, obj);
				if (obj->isMarkForDestruction())
					currentScreen->ClearScreenObject(obj);
				if (tempCreature->isMarkForDestruction())
					currentScreen->ClearScreenObject(tempCreature);
			}
		}
	}
}

// this function prints the game/level stats (scores, lives,current level and current turn), refreshes each time there is a change
void TheMathGame::PrintScores()const
{
	gotoxy(0, 0);
	cout << "Score: " << player1.GetScore();
	gotoxy(55, 0);
	cout << "Score: " << player2.GetScore();
	gotoxy(0, 2);
	cout << "Lives: " << player1.GetNumberOfLives();
	gotoxy(55, 2);
	cout << "Lives: " << player2.GetNumberOfLives();
	gotoxy(30, 0);
	cout << "Level " << currentLevel;
	gotoxy(30, 1);
	cout << "Current Turn " << currentTurn;
	gotoxy(10, 2);
	cout << "Bullets " << player1.GetNumberOfBullets();
	gotoxy(65, 2);
	cout << "Bullets " << player2.GetNumberOfBullets();
}

//this function will handle the players keystorkes and change theier direction accordingly
void TheMathGame::keyStrokeManager(const list<char>& keyHits)
{
	char keyHit;
	bool player1KbHit, player2KbHit;
	player1KbHit = player2KbHit = false;
	//iteration on the key hits from both players, 
	for (list<char>::const_iterator itr = keyHits.cbegin(); itr != keyHits.cend() && (!player1KbHit || !player2KbHit); ++itr)
	{
		keyHit = *itr;
		//checks if the current keystroke valid for one of the players
		//if so, changes the direction of the correct player
		if (!player1KbHit && player1.GetKeyboardKeys().find(keyHit) != string::npos)// player 1 hit a valid key
		{
			player1KbHit = true; // player 1 already hit a key this turn
			player1.SetDirection(MapKeyToDirection(keyHit, player1)); // set the direction of player 1 accoridng to the key he hit
		}
		if (!player2KbHit && player2.GetKeyboardKeys().find(keyHit) != string::npos) // player2 hit a valid key
		{
			player2KbHit = true; // player 2 already hit a key this turn
			player2.SetDirection(MapKeyToDirection(keyHit, player2));// set the direction of player 2 accoridng to the key he hit
		}
	}
}


// this function manages the player movment, checks if the next move will hit another player
//or will hit a number, and handles all the possiblties
void TheMathGame::PlayerMovment(Player & p, Equation & eq)
{
	Point toMove = p.getPointToMove();
	ScreenObject * obj = currentScreen->GetScreenObject(toMove.GetX(), toMove.GetY());

	if (obj == nullptr){
		clearAndMove(p, toMove, nullptr);
	}
	else if (dynamic_cast<SolutionPosabilty*>(obj) != nullptr)
	{
		CheckSolution(eq, obj, p); // check  if its a valid solution
		clearAndMove(p, toMove, obj); // clear the old object and move the player there instead
	}
	else
	{ // TAKE NOTE TO ADD THIS
		CollisionManager::collesion(&p, obj);
		if (p.isMarkForDestruction())
			currentScreen->ClearScreenObject(&p);
		if (obj->isMarkForDestruction())
			currentScreen->ClearScreenObject(obj);
	}
}

//this function clears the current player placment, and if there is an object in the
//players way, and prints the player in the new position.
void TheMathGame::clearAndMove(MovingScreenObject& p, const Point& toMove, ScreenObject* obj)
{
	if (obj != nullptr)// if there is an object in the movment position
		currentScreen->ClearScreenObject(obj); // clear the object

	currentScreen->ClearScreenObject(&p); // clear the old player position formt he screen
	p.Move(toMove); // move the player
	currentScreen->SetPositionForScreenObject(&p); // set the player position in the screen
}

//this function gets the equation of the player, and the object the player gathered
//and changes the player data if the solution was correct 
//or did he used one of his lives.
void TheMathGame::CheckSolution(Equation& eq, const ScreenObject* obj, Player& p)
{
	SolutionType currentSolutionStatus = eq.IsSolution(obj->GetData());

	if (currentSolutionStatus == IS_SOLUTION)
		p.FoundTheSolution(); // solution found!!!
	else if (currentSolutionStatus == WRONG_SOLUTION)
		p.WrongSolution(); // Not the solution better luck next time!!!
	else if (currentSolutionStatus == PARTIAL_SOLUTION)
		eq.Draw(); // the solution posability is ok so draw the upadated equation
}

Direction::value TheMathGame::MapKeyToDirection(const char& keyHit, Player& p)
{
	//gets a player and keystoke, 
	//return the direction by mapping the keystroke to the player possibile movments
	
	if (p.GetKeyboardKeys().at(LEFT) == keyHit)
		return Direction::LEFT;

	if (p.GetKeyboardKeys().at(UP) == keyHit)
		return Direction::UP;

	if (p.GetKeyboardKeys().at(RIGHT) == keyHit)
		return Direction::RIGHT;

	if (p.GetKeyboardKeys().at(DOWN) == keyHit)
		return Direction::DOWN;

	if (p.GetKeyboardKeys().at(SHOOT) == keyHit)
	{
		if (p.GetNumberOfBullets() > 0)
		{
			p.RemoveBullet();
			AddNewBullet(Bullet(p.getPointToMove(), p.GetDirection()));
		}
	}

	return p.GetDirection();
	
}


//this funciton will draw the 2 equations
void TheMathGame::DrawEquations()const

{
	equation1.Draw();
	equation2.Draw();
}

//this function will retrun a color for the screen text based on the current level. each level we will replace the screen color
Color TheMathGame::GetColorForText()const
{
	return (Color)((currentLevel % 15) + 1); // we have 15 colors from 1 to 15
}

void TheMathGame::addNewCreature(Creature * a){
	creatureList.push_front(a);
	currentScreen->SetPositionForScreenObject(a);
	a->Draw();
}

void TheMathGame::AddNewBullet(Bullet b)
{
	Bullet* newB = new Bullet(b.GetPosition(), b.GetDirection());
	bulletList.push_front(newB);
	currentScreen->SetPositionForScreenObject(newB);
	b.Draw();
}

//helper methood adds new bullet to players ( will be called every 200 turns)
void TheMathGame::AddBulletToPlayers()
{
	player1.AddBullet();
	player2.AddBullet();
}