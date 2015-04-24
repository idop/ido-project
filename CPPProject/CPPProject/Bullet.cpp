#include "Bullet.h"
#include "io_utils.h"

using namespace std;

void Bullet::Draw()const
{
	gotoxy(position.getX(), position.getY());
	cout << bullet;
}

void Bullet::Clear()const
{
	gotoxy(position.getX(), position.getY());
	cout << ' ';
}