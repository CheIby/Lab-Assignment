#include <stdio.h>
#include <Windows.h>
#include<conio.h>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void drawShip(int x, int y)
{
	gotoxy(x, y);
	printf("<-0->");
}

void eraseShip(int x, int y)
{
	gotoxy(x, y);
	printf("     ");
}

int main()
{
	char ch = ' ';
	int x = 38, y = 20;
	drawShip(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x>0)
			{
				eraseShip(x, y);
				drawShip(--x, y);
			}
			if (ch == 'd' && x<80)
			{
				eraseShip(x, y);
				drawShip(++x, y);
			}
			if (ch == 'w' && y>0)
			{
				eraseShip(x, y);
				drawShip(x, --y);
			}
			if (ch == 's' && y<100)
			{
				eraseShip(x, y);
				drawShip(x, ++y);
			}
			fflush(stdin);
		}
		Sleep(50);
	} while (ch != 'x');
	return 0;
}