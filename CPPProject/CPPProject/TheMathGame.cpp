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
	//for each player we echeck if he has lives to keep on playing , and manage his movment.
	if (player1.GetNumberOfLives() != 0)
		PlayerMovment(GetPointToMove(player1), player1, equation1);

	if (player2.GetNumberOfLives() != 0)
		PlayerMovment(GetPointToMove(player2), player2, equation2);

	//initialazing the end turn checks
	EndTurn();
}


//this function handles all end of turn events. checks if a player lost all his lives 
//or if the level should end (player solved the equation, all players lost thier lives , the level passed the possible max turn
void TheMathGame::EndTurn()
{
	++currentTurn;

	if (player1.GetNumberOfLives() == 0) // if player1 lost all  of his lives  remove him from the screen
		currentScreen->ClearScreenObject(&player1);

	if (player2.GetNumberOfLives() == 0) // if player2 lost all  of his lives  remove him from the screen
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

	//bulletList.clear();
	PrintScores();
}

void TheMathGame::doSubIteration()
{
	runBulletList();
}

void TheMathGame::runBulletList()
{
	for (list<Bullet*>::const_iterator itr = bulletList.cbegin(), end = bulletList.cend(); itr != end; ++itr)
	{
		Bullet* tempBullet = *itr;
		if (tempBullet->getIsLive())
		{
			Point toMove = GetPointToMove(*tempBullet);
			ScreenObject* obj = currentScreen->GetScreenObject(toMove.GetX(), toMove.GetY());
			if (obj == nullptr)
				clearAndMove(*tempBullet, toMove, NULL);
			else if (obj->GetType() == 'n')
			{
				currentScreen->ClearScreenObject(obj);
				currentScreen->ClearScreenObject(tempBullet);
				tempBullet->Collesion();
			}
			else
			{
				currentScreen->ClearScreenObject(obj);
				currentScreen->ClearScreenObject(tempBullet);
				obj->Collesion();
				tempBullet->Collesion();
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
void TheMathGame::PlayerMovment(const Point& toMove, Player& p, Equation& eq)
{
	ScreenObject* obj = nullptr;

	switch (p.GetDirection())
	{
	case Direction::LEFT:
		obj = currentScreen->GetScreenObject(toMove.GetX(), toMove.GetY());
		// check if the new place to move  is free
		if (obj == nullptr)
			clearAndMove(p, toMove, nullptr);
		// check if we are going to eat a solution number
		else if (obj->GetType() == 'n')
		{
			CheckSolution(eq, obj, p); // check  if its a valid solution
			clearAndMove(p, toMove, obj); // clear the old object and move the player there instead

			//else the object we are colliding with is the other player which means we will not move
			break;
		case Direction::UP:
			obj = currentScreen->GetScreenObject(toMove.GetX(), toMove.GetY());
			// check if  the new place to move  is free
			if (obj == nullptr)
				clearAndMove(p, toMove, nullptr);
			// check if we are going to eat a solution number
			else if (obj->GetType() == 'n')
			{
				CheckSolution(eq, obj, p); // check  if its a valid solution
				clearAndMove(p, toMove, obj);// clear the old object and move the player there instead
			}
			//else the bject we are colliding with is the other player there for we will not move
			break;
		case Direction::RIGHT:
			obj = currentScreen->GetScreenObject(toMove.GetX(), toMove.GetY());
			if (obj == nullptr) // check  if the new place to move  is free
				clearAndMove(p, toMove, nullptr);
			else if (obj->GetType() == 'n') // check if we are going to eat a solution number
			{
				CheckSolution(eq, obj, p);// check  if its a valid solution
				clearAndMove(p, toMove, obj); // clear the old object and move the player there instead
			}//else the bject we are colliding with is the other player there for we will not move
			break;
		case Direction::DOWN:
			obj = currentScreen->GetScreenObject(toMove.GetX(), toMove.GetY());
			if (obj == nullptr) // check if the new place to move  is free
				clearAndMove(p, toMove, nullptr);
			else if (obj->GetType() == 'n') // check if we are going to eat a solution number
			{
				CheckSolution(eq, obj, p); // check  if its a valid solution
				clearAndMove(p, toMove, obj);// clear the old object and move the player there instead
			}
			//else the bject we are colliding with is the other player there for we will not move
			break;
		default: // we should not get here
			break;
		}
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
	switch (p.GetPlayerChar())
	{
	case '@':
		switch (keyHit)
		{
		case 'a':
			return Direction::LEFT;
		case 'w':
			return Direction::UP;
		case 'd':
			return Direction::RIGHT;
		case 'x':
			return Direction::DOWN;
		case 'z':
			if (p.GetNumberOfBullets() > 0)
			{
				p.RemoveBullet();
				AddNewBullet(Bullet(GetPointToMove(p), p.GetDirection()));
			}
			break;
		default: // we should not get here
			break;
		}
		break;

	case '#':
		switch (keyHit)
		{
		case 'j':
			return Direction::LEFT;
		case 'i':
			return Direction::UP;
		case 'l':
			return Direction::RIGHT;
		case 'm':
			return Direction::DOWN;
		case 'n':
			if (p.GetNumberOfBullets() > 0)
			{
				p.RemoveBullet();
				AddNewBullet(Bullet(GetPointToMove(p), p.GetDirection()));
			}
			break;
		default: // we should not get here
			break;
		}
		break;
	}
	return p.GetDirection();
}

//this function manages the next move of the player, loops around the screen
Point TheMathGame::GetPointToMove(const MovingScreenObject& p)
{
	return p.GetPosition().GetPointToMoveFromDirection(p.GetDirection()); // TODO CHANGE THIS PART TO FINISH THE NEW LOGIC
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

void TheMathGame::AddNewBullet(Bullet b)
{
	Bullet* newB = new Bullet(b.GetPosition(), b.GetDirection());
	bulletList.push_front(newB);
	currentScreen->SetPositionForScreenObject(newB);
	newB->Draw();
}

//helper methood adds new bullet to players ( will be called every 200 turns)
void TheMathGame::AddBulletToPlayers()
{
	player1.AddBullet();
	player2.AddBullet();
}