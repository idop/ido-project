#include "TheMathGame.h"
#include "io_utils.h"


void TheMathGame::startLevel()
{
	clear_screen();
	++currentLevel;
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
	player1KbHit = player2KbHit = false;

	if (currentTurn % 2 == 0)
		currentScreen->CreateNewSolutionPosability(currentLevel);
	//TODO handle colisions and player movement
	// get keystrokes from keyhist list untill the end of the list or until both players got a valid keystroke
	for (list < char >::const_iterator itr = keyHits.cbegin(); itr != keyHits.cend() && (!player1KbHit || !player2KbHit); ++itr)  
	{
		keyHit = *itr;
		if (!player1KbHit && player1.GetKeyboardKeys().find(keyHit))
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
		if (!player2KbHit && player2.GetKeyboardKeys().find(keyHit))
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
	player1.Clear();
	player1.Move();
	player1.Draw();
	player2.Clear();
	player2.Move();
	player2.Draw();
	EndTurn();
}

void TheMathGame::doSubIteration()
{

}

void TheMathGame::EndTurn()
{
	++currentTurn;
	if (player1.IsSolutionFound() || player2.IsSolutionFound())
	{
		currentScreen->CleanScreen(); // free memory of all dyemic objects
		delete currentScreen; // free the memory for the screen object
		levelDone = true;
		clear_screen();
		gotoxy(35, 12);
		cout << "Well Done";
		Sleep(1500); 
	}
	else if (currentTurn >= MAX_TURNS_PER_LEVEL)
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