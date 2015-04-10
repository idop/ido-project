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
	//TODO handle colisions and player movement
	if (currentTurn % 2 == 0)
		currentScreen->CreateNewSolutionPosability(currentLevel);
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