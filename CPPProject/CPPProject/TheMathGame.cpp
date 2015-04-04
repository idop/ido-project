#include "TheMathGame.h"
#include "io_utils.h"

bool TheMathGame::isLevelDone()const
{
	return (player1.GetPosition().getX() == player2.GetPosition().getX());
}
;

void TheMathGame::startLevel()
{
	clear_screen();
	++currentLevel;
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
}

void TheMathGame::doIteration(const list<char>& keyHits)
{
	player1.Clear();
	player1.Move();
	player1.Draw();
	player2.Clear();
	player2.Move();
	player2.Draw();
}

void TheMathGame::doSubIteration()
{


}