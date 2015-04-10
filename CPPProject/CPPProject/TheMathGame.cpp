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


void TheMathGame::startLevel(unsigned int level)
{
	/* each Start level the function will 
	 * initiallzie player1 and player2 to thier defualt values
	 * and put the players in the default places on screen
	 */

	clear_screen();
	levelDone = false;
	currentLevel = level;
	currentTurn = 0;
	equation1.Init(currentLevel);
	equation1.Draw();
	equation2.Init(currentLevel);
	equation2.Draw();
	player1.SetToStart(P1_DEFULT_POSITION , P1_DEFULT_DIRECTION);
	player1.Draw();
	player2.SetToStart(P2_DEFULT_POSITION, P2_DEFULT_DIRECTION);
	player2.Draw();

	PrintScores();

	currentScreen = new Screen;
	currentScreen->SetPositionForScreenObject(&player1);
	currentScreen->SetPositionForScreenObject(&player2);
}

void TheMathGame::doIteration(const list<char>& keyHits)  
{
	//for better game play we reduce the refresh rate of new solution possiblties
	if (currentTurn % 2 == 0)
		currentScreen->CreateNewSolutionPosability(currentLevel);

	// get keystrokes from keyhist list untill the end of the list or until both players got a valid keystroke
	keyStrokeManager(keyHits); 

	//for each player we echeck if he has lives to keep on playing , and manage his movment.
	if (player1.getNumberOfLives() != 0)
		PlayerMovment(GetPointToMove(player1), player1, equation1);

	if (player2.getNumberOfLives() != 0)
		PlayerMovment(GetPointToMove(player2), player2, equation2);
	
	//initialazing the end turn checks
	EndTurn();
}

void TheMathGame::EndTurn()
{
	++currentTurn;

	if (player1.getNumberOfLives() == 0) // if player1 lost all  of his lives  remove him from the screen
		currentScreen->ClearScreenObject(&player1);
	
	if (player2.getNumberOfLives() == 0) // if player2 lost all  of his lives  remove him from the screen
		currentScreen->ClearScreenObject(&player2);
	
	if (player1.IsSolutionFound() || player2.IsSolutionFound()) // one of the players solved the equations
	{
		currentScreen->CleanScreen(); // free memory of all dyemic objects
		delete currentScreen; // free the memory for the screen object
		levelDone = true;
		clear_screen();
		gotoxy(35, 12);
		cout << "Well Done";
		Sleep(1500); 
	}
	else if (currentTurn >= MAX_TURNS_PER_LEVEL || (player2.getNumberOfLives() == 0 && player1.getNumberOfLives() == 0)) // current screen reached its max turns limit
	{
		currentScreen->CleanScreen(); // free memory of all dyemic objects
		delete currentScreen; // free the memory for the screen object
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

}

void TheMathGame::PrintScores(){

	//prints the stats menu, refreshes each time there is a change

	gotoxy(0, 0);
	cout << "Score: " << player1.getScore();
	gotoxy(70, 0);
	cout << "Score: " << player2.getScore();
	gotoxy(0, 2);
	cout << "Lives: " << player1.getNumberOfLives();
	gotoxy(70, 2);
	cout << "Lives: " << player2.getNumberOfLives();
	gotoxy(35, 0);
	cout << "Level " << currentLevel;
	gotoxy(35, 1);
	cout << "Current Turn " << currentTurn;

}

void TheMathGame::keyStrokeManager(const list<char> & keyHits){

	char keyHit;
	bool player1KbHit, player2KbHit;
	player1KbHit = player2KbHit = false;
	//iteration on the key hits from both players, 
	for (list < char >::const_iterator itr = keyHits.cbegin(); itr != keyHits.cend() && (!player1KbHit || !player2KbHit); ++itr)
	{
		keyHit = *itr;
		//checks if the current keystroke valid for one of the players
		//if so, changes the direction of the correct player
		if (!player1KbHit && player1.GetKeyboardKeys().find(keyHit) != string::npos)
		{
			player1KbHit = true;
			player1.SetDirection(MapKeyToDirection(keyHit, player1));
		}
		if (!player2KbHit && player2.GetKeyboardKeys().find(keyHit) != string::npos)
		{
			player2KbHit = true;
			player2.SetDirection(MapKeyToDirection(keyHit, player2));
		}
	}
}

void TheMathGame::PlayerMovment(const Point & toMove, Player & p, Equation & eq){

	//manages the player movment, checks if the next move will hit another player
	//or will hit a number, and handles all the possiblties

	ScreenObject * obj = NULL;

	switch (p.getdirection())
	{
	case Direction::LEFT:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		// check the new place to move  is free
		if (obj == NULL)
			clearAndMove(p, toMove, NULL);
		// check if we are going to eat a solution number
		else if (obj->Type() == 'n') {
			{
				CheckSolution(eq, obj, p);
				clearAndMove(p, toMove, obj);
			}
			//else the object we are colliding with is the other player which means we will not move
			break;
	case Direction::UP:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		// check the new place to move  is free
		if (obj == NULL)
			clearAndMove(p, toMove, NULL);
		// check if we are going to eat a solution number
		else if (obj->Type() == 'n') {
			CheckSolution(eq, obj, p);
			clearAndMove(p, toMove, obj);
		}
		//else the bject we are colliding with is the other player there for we will not move
		break;
	case Direction::RIGHT:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		if (obj == NULL) // check the new place to move  is free
			clearAndMove(p, toMove, NULL);
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			CheckSolution(eq, obj, p);
			clearAndMove(p, toMove, obj);
		}//else the bject we are colliding with is the other player there for we will not move
		break;
	case Direction::DOWN:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		if (obj == NULL) // check the new place to move  is free
			clearAndMove(p, toMove, NULL);
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			CheckSolution(eq, obj, p);
			clearAndMove(p, toMove, obj);
		}
		//else the bject we are colliding with is the other player there for we will not move
		break;
	default: // we should not get here
		break;
		}

	}
}

void TheMathGame::clearAndMove(Player & p, const Point & toMove, ScreenObject * obj){
	
	//clears the current player placment, and if there is an object in the
	//players way, and prints the player in the new position.

	if (obj != NULL)
		currentScreen->ClearScreenObject(obj);

	currentScreen->ClearScreenObject(&p);
	p.Move(toMove);
	p.Draw();
	currentScreen->SetPositionForScreenObject(&p);
}

void TheMathGame::CheckSolution(Equation eq, const ScreenObject * obj, Player & p){

	//gets the equation of the player, and the object the player gathered
	//and changes the player data if the solution was correct 
	//or did he used one of his lives.

	if (eq.IsSolution(obj->GetData()))
		p.FoundTheSolution();
	else
		p.WrongSolution();
}

Direction::value TheMathGame::MapKeyToDirection(const char & keyHit, const Player & p)
{

	//gets a player and keystoke, 
	//return the direction by mapping the keystroke to the player possibile movments
	switch (p.getPlayerChar()){

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
		default: // we should not get here
			break;
		}
		break;
	}
}

Point TheMathGame::GetPointToMove(const Player & p)
{
	//manages the next move of the player, loops around the screen

	switch (p.getdirection())
	{
	case Direction::LEFT:
		if (p.GetPosition().getX() == 0) // check if the player is going to move outside of the screen limit
			return Point(79, p.GetPosition().getY());
		else
			return Point(p.GetPosition().getX() - 1, p.GetPosition().getY());
		break;
	case Direction::RIGHT:
		if (p.GetPosition().getX() == 79) // check if the player is going to move outside of the screen limit
			return Point(0, p.GetPosition().getY());
		else
			return Point(p.GetPosition().getX() + 1, p.GetPosition().getY());
		break;
	case Direction::UP:
		if (p.GetPosition().getY() == 3) // check if the player is going to move outside of the screen limit
			return Point(p.GetPosition().getX(), 23);
		else
			return Point(p.GetPosition().getX(), p.GetPosition().getY() - 1);
		break;
	case Direction::DOWN:
		if (p.GetPosition().getY() == 23) // check if the player is going to move outside of the screen limit
			return Point(p.GetPosition().getX(), 3);
		else
			return Point(p.GetPosition().getX(), p.GetPosition().getY() + 1);
		break;
	default:// we should not get here
		break;
	}
}
