#include "TheMathGame.h"
#include "io_utils.h"


void TheMathGame::startLevel(unsigned int level)
{
	clear_screen();
	currentLevel = level;
	levelDone = false;
	currentTurn = 0;
	equation1.Init(currentLevel);
	equation1.Draw();
	equation2.Init(currentLevel);
	equation2.Draw();
	player1.SetToStart(P1_DEFULT_POSITION , P1_DEFULT_DIRECTION);
	player1.Draw();
	player2.SetToStart(P2_DEFULT_POSITION, P2_DEFULT_DIRECTION);
	player2.Draw();
	gotoxy(0, 0);
	cout << "Score: " << player1.getScore();
	gotoxy(35, 0);
	cout << "Level " << currentLevel;
	gotoxy(70, 0);
	cout << "Score: " << player2.getScore();
	gotoxy(0, 2);
	cout << "Lives: " << player1.getNumberOfLives();
	gotoxy(70, 2);
	cout << "Lives: " << player2.getNumberOfLives();

	currentScreen = new Screen;
	currentScreen->SetPositionForScreenObject(&player1);
	currentScreen->SetPositionForScreenObject(&player2);
}

void TheMathGame::doIteration(const list<char>& keyHits)  
{
	char keyHit;
	bool player1KbHit, player2KbHit;
	Point toMove;
	ScreenObject * obj =NULL;
	player1KbHit = player2KbHit = false;

	if (currentTurn % 2 == 0)
		currentScreen->CreateNewSolutionPosability(currentLevel);
	//TODO Beautify
	// get keystrokes from keyhist list untill the end of the list or until both players got a valid keystroke
	for (list < char >::const_iterator itr = keyHits.cbegin(); itr != keyHits.cend() && (!player1KbHit || !player2KbHit); ++itr)  
	{
		keyHit = *itr;
		if (!player1KbHit && player1.GetKeyboardKeys().find(keyHit) != string::npos)
		{
			switch (keyHit)
			{
			case 'a':
				player1.SetDirection(Direction::LEFT);
				player1KbHit = true;
				break;
			case 'w':
				player1.SetDirection(Direction::UP);
				player1KbHit = true;
				break;
			case 'd':
				player1.SetDirection(Direction::RIGHT);
				player1KbHit = true;
				break;
			case 'x':
				player1.SetDirection(Direction::DOWN);
				player1KbHit = true;
				break;
			default: // we should not get here
				break;
			}
		}
		if (!player2KbHit && player2.GetKeyboardKeys().find(keyHit) != string::npos)
		{
			switch (keyHit)
			{
			case 'j':
				player2.SetDirection(Direction::LEFT);
				player2KbHit = true;
				break;
			case 'i':
				player2.SetDirection(Direction::UP);
				player2KbHit = true;
				break;
			case 'l':
				player2.SetDirection(Direction::RIGHT);
				player2KbHit = true;
				break;
			case 'm':
				player2.SetDirection(Direction::DOWN);
				player2KbHit = true;
				break;
			default: // we should not get here
				break;
			}
		}
	}
	//TODO Colllsion, beautify and handle player death

	//collision managment for player1
	if (player1.getNumberOfLives() != 0)
	{ 
	toMove = GetPointToMove(player1);
	switch (player1.getdirection())
	{
	case Direction::LEFT:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		if (obj == NULL) // check the new place to move  is free
		{
			currentScreen->ClearScreenObject(&player1);
			player1.Move(toMove);
			player1.Draw();
			currentScreen->SetPositionForScreenObject(&player1);
		}
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			if (equation1.IsSolution(obj->GetData()))
				player1.FoundTheSolution();
			else
			{
				player1.WrongSolution();
				gotoxy(0, 2);
				cout << "Lives: " << player1.getNumberOfLives();
			}
			currentScreen->ClearScreenObject(obj);
			obj = NULL;
			currentScreen->ClearScreenObject(&player1);
			player1.Move(toMove);
			player1.Draw();
			currentScreen->SetPositionForScreenObject(&player1);

		}//else the bject we are colliding with is the other player there for we will not move
			break;
	case Direction::UP:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		if (obj == NULL) // check the new place to move  is free
		{
			currentScreen->ClearScreenObject(&player1);
			player1.Move(toMove);
			player1.Draw();
			currentScreen->SetPositionForScreenObject(&player1);
		}
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			if (equation1.IsSolution(obj->GetData()))
				player1.FoundTheSolution();
			else
			{
				player1.WrongSolution();
				gotoxy(0, 2);
				cout << "Lives: " << player1.getNumberOfLives();
			}
			currentScreen->ClearScreenObject(obj);
			obj = NULL;
			currentScreen->ClearScreenObject(&player1);
			player1.Move(toMove);
			player1.Draw();
			currentScreen->SetPositionForScreenObject(&player1);
		}//else the bject we are colliding with is the other player there for we will not move
			break;
	case Direction::RIGHT:
		obj = currentScreen->GetScreenObject(toMove.getX() , toMove.getY());
		if (obj == NULL) // check the new place to move  is free
		{
			currentScreen->ClearScreenObject(&player1);
			player1.Move(toMove);
			player1.Draw();
			currentScreen->SetPositionForScreenObject(&player1);
		}
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			if (equation1.IsSolution(obj->GetData()))
				player1.FoundTheSolution();
			else
			{
				player1.WrongSolution();
				gotoxy(0, 2);
				cout << "Lives: " << player1.getNumberOfLives();
			}
			currentScreen->ClearScreenObject(obj);
			obj = NULL;
			currentScreen->ClearScreenObject(&player1);
			player1.Move(toMove);
			player1.Draw();
			currentScreen->SetPositionForScreenObject(&player1);
		}//else the bject we are colliding with is the other player there for we will not move
			break;
	case Direction::DOWN:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		if (obj == NULL) // check the new place to move  is free
		{
			currentScreen->ClearScreenObject(&player1);
			player1.Move(toMove);
			player1.Draw();
			currentScreen->SetPositionForScreenObject(&player1);
		}
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			if (equation1.IsSolution(obj->GetData()))
				player1.FoundTheSolution();
			else
			{
				player1.WrongSolution();
	gotoxy(70, 2);
	cout << "Lives: " << player2.getNumberOfLives();
			}
			currentScreen->ClearScreenObject(obj);
			obj = NULL;
			currentScreen->ClearScreenObject(&player1);
			player1.Move(toMove);
			player1.Draw();
			currentScreen->SetPositionForScreenObject(&player1);
		}//else the bject we are colliding with is the other player there for we will not move
			break;
		default: // we should not get here
			break;
	}
	}
//PLAYER 2 COLLISION
	if (player2.getNumberOfLives() != 0)
	{
	toMove = GetPointToMove(player2);
	switch (player2.getdirection())
	{
	case Direction::LEFT:
		
		
		obj = currentScreen->GetScreenObject(toMove.getX() , toMove.getY());
		if (obj == NULL) // check the new place to move  is free
		{
			currentScreen->ClearScreenObject(&player2);
			player2.Move(toMove);
			player2.Draw();
			currentScreen->SetPositionForScreenObject(&player2);
		}
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			if (equation1.IsSolution(obj->GetData()))
				player2.FoundTheSolution();
			else
			{
				player2.WrongSolution();
				gotoxy(70, 2);
				cout << "Lives: " << player2.getNumberOfLives();
			}
			currentScreen->ClearScreenObject(obj);
			obj = NULL;
			currentScreen->ClearScreenObject(&player2);
			player2.Move(toMove);
			player2.Draw();
			currentScreen->SetPositionForScreenObject(&player2);
		}//else the bject we are colliding with is the other player there for we will not move
		break;
	case Direction::UP:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		if (obj == NULL) // check the new place to move  is free
		{
			currentScreen->ClearScreenObject(&player2);
			player2.Move(toMove);
			player2.Draw();
			currentScreen->SetPositionForScreenObject(&player2);
		}
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			if (equation1.IsSolution(obj->GetData()))
				player2.FoundTheSolution();
			else
			{
				player2.WrongSolution();
				gotoxy(70, 2);
				cout << "Lives: " << player2.getNumberOfLives();
			}
			currentScreen->ClearScreenObject(obj);
			obj = NULL;
			currentScreen->ClearScreenObject(&player2);
			player2.Move(toMove);
			player2.Draw();
			currentScreen->SetPositionForScreenObject(&player2);
		}//else the bject we are colliding with is the other player there for we will not move
		break;
	case Direction::RIGHT:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		if (obj == NULL) // check the new place to move  is free
		{
			currentScreen->ClearScreenObject(&player2);
			player2.Move(toMove);
			player2.Draw();
			currentScreen->SetPositionForScreenObject(&player2);
		}
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			if (equation1.IsSolution(obj->GetData()))
				player2.FoundTheSolution();
			else
			{
				player2.WrongSolution();
				gotoxy(70, 2);
				cout << "Lives: " << player2.getNumberOfLives();
			}
			currentScreen->ClearScreenObject(obj);
			obj = NULL;
			currentScreen->ClearScreenObject(&player2);
			player2.Move(toMove);
			player2.Draw();
			currentScreen->SetPositionForScreenObject(&player2);
		}//else the bject we are colliding with is the other player there for we will not move
		break;
	case Direction::DOWN:
		obj = currentScreen->GetScreenObject(toMove.getX(), toMove.getY());
		if (obj == NULL) // check the new place to move  is free
		{
			currentScreen->ClearScreenObject(&player2);
			player2.Move(toMove);
			player2.Draw();
			currentScreen->SetPositionForScreenObject(&player2);
		}
		else if (obj->Type() == 'n') // check if we are going to eat a solution number
		{
			if (equation1.IsSolution(obj->GetData()))
				player2.FoundTheSolution();
			else
			{
				player2.WrongSolution();
				gotoxy(70, 2);
				cout << "Lives: " << player2.getNumberOfLives();
			}
			currentScreen->ClearScreenObject(obj);
			obj = NULL;
			currentScreen->ClearScreenObject(&player2);
			player2.Move(toMove);
			player2.Draw();
			currentScreen->SetPositionForScreenObject(&player2);
		}//else the bject we are colliding with is the other player there for we will not move
		break;
	default: // we should not get here
		break;
	}

 }
	EndTurn();
}

void TheMathGame::doSubIteration()
{

}

//this function will end each turn
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
}

Point TheMathGame::GetPointToMove(const Player & p)
{
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
			return Point(p.GetPosition().getX(), p.GetPosition().getY()-1);
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