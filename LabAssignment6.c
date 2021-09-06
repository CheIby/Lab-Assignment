#include <stdio.h>
#include <Windows.h>
#include<conio.h>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible; 
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void drawShip(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf("<-0->");
}

void eraseShip(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf("     ");
}

void drawBullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf("^");
}

void eraseBullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

int main()
{
	char ch = ' ';
	int check=0;
	int bullet[5] = { 0 };
	int posX[5], posY[5];
	int x = 38, y = 20;
	drawShip(x, y);
	setcursor(0);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a')
			{
				check = 1;
			}
			if (ch == 'd' && x<80)
			{
				check = 2;
			}
			if (ch == 's' && y<100)
			{
				check = 0;
			}
			if (ch == ' ')
			{
				for (int i = 0; i < 5; i++)
				{
					if (bullet[i] == 0)
					{
						bullet[i] = 1;
						posX[i] = x + 2;
						posY[i] = y - 1;
						break;
					}
				}
			}
			fflush(stdin);
		}
		if (check == 1 && x > 0)
		{
			eraseShip(x, y);
			drawShip(--x, y);
		}
		if (check == 2 && x < 80)
		{
			eraseShip(x, y);
			drawShip(++x, y);
		}
		if (check == 0)
		{
			eraseShip(x, y);
			drawShip(x, y);
		}
		for (int i = 0; i < 5; i++)
		{
			if (bullet[i] == 1)
			{
				eraseBullet(posX[i], posY[i]);
				drawBullet(posX[i], --posY[i]);
				if (posY[i] <= 0)
				{
					bullet[i] = 0;
					eraseBullet(posX[i], posY[i]);
				}
			}
		}
		Sleep(50);
	} while (ch != 'x');
	return 0;
}
