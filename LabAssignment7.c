#include <stdio.h>
#include <Windows.h>
#include<conio.h>
#include <time.h>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setcursor(boolean visible)
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

char cursor(int x, int y) 
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
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
	Beep(2000, 10);
}

void eraseBullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

void drawStar(int x, int y)
{
	gotoxy(x, y);
	setcolor(3, 4);
	printf("*");
}

void showscore(int score)
{
	gotoxy(0, 0);
	printf("Score : %d", score);
}

int main()
{
	srand(time(0));
	char ch = ' ';
	int score = 0;
	int check=0;
	int bullet[5] = { 0 };
	int posX[5], posY[5],checkPosX[5],checkPosY[5];
	char checkBu[5];
	int x = 38, y = 20;
	for (int i = 0; i < 20; i++)
	{
		drawStar(rand() % 61 + 10, rand() % 4 + 2);
	}
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
				if (cursor(posX[i], posY[i]-1) == '*')
				{
					bullet[i] = 0;
					eraseBullet(posX[i], --posY[i]);
					Beep(1000, 100);
					score += 10;
					drawStar(rand() % 61 + 10, rand() % 4 + 2);
				}
				else
				{
					drawBullet(posX[i], --posY[i]);
				}
				if (posY[i] <= 0)
				{
					bullet[i] = 0;
					eraseBullet(posX[i], posY[i]);
				}
			}
		}
		showscore(score);
		Sleep(50);
	} while (ch != 'x');
	return 0;
}

