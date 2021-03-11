
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define tableXpos 40
#define tableYpos 8

struct xycoord {
	short pos[19][19];
	short xpos;
	short ypos;
	bool borw;
};

void movetoxy(int, int);
void clearScreen();
char anyKey();
void startscreen();
void tableOverlay();
int GameControl(xycoord*);
int checkPos(xycoord);
void sysText(xycoord, int);

int blackstack = 0;
int whitestack = 0;
int main(void)
{
	startscreen();
	xycoord dpos{ { 0 }, 9, 9, false }; // 중앙
	tableOverlay();
	movetoxy(dpos.xpos * 2, dpos.ypos);
	if (GameControl(&dpos) == 1) sysText(dpos, 5);
	else sysText(dpos, 6);

	movetoxy(50, 19);
	std::cout << "게임 끝!";

	anyKey();

}

int GameControl(xycoord* p)
{
	int check = 0;
	char keybuff;
	int xbuff, ybuff;
	while (1)
	{
		xbuff = p->xpos;
		ybuff = p->ypos;
		keybuff = 0;
		while (keybuff != 32)
		{
			switch (keybuff = anyKey())
			{
			case (LEFT):
			{
				if (xbuff != 0) xbuff--;
				break;
			}

			case (RIGHT):
			{
				if (xbuff != 18) xbuff++;
				break;
			}

			case (DOWN):
			{
				if (ybuff != 18) ybuff++;
				break;
			}

			case (UP):
			{
				if (ybuff != 0) ybuff--;
				break;
			}
			}
			movetoxy(xbuff * 2, ybuff);

		}
		p->xpos = xbuff;
		p->ypos = ybuff;
		check = checkPos(*p);
		if (check == 0 && p->borw == false) { // 흑=1, 백=2, 돌이 없을때만 둠
			std::cout << "○";
			p->borw = true; // 백턴으로
			p->pos[p->xpos][p->ypos] = 1;
		}
		else if (check == 0 && p->borw == true)
		{
			std::cout << "●";
			p->borw = false;
			p->pos[p->xpos][p->ypos] = 2;
		}
		else if (check == 1)
		{
			sysText(*p, check); // 돌이있을경우 출력후 다시 돌아감
			continue;
		}

		check = checkPos(*p);
		if (checkPos(*p) == 5) return 1;
		if (checkPos(*p) == 6) return 2;
		movetoxy(p->xpos * 2, p->ypos);

		check = checkPos(*p);

		sysText(*p, 0); // 지우기
	}

	return 0;

}

int checkPos(xycoord p) // 
{

	int k = 0;
	for (int i = 0; i <= 18; i++)  // 가로
	{
		for (int j = 0; j <= 18; j++)
		{
			if (p.pos[j][i] == 1)
			{
				blackstack++;
				whitestack = 0;
			}
			else if (p.pos[j][i] == 2)
			{
				blackstack = 0;
				whitestack++;
			}
			else {
				whitestack = 0;
				blackstack = 0;
			}
			if (blackstack == 5) return 5;
			if (whitestack == 5) return 6;
		}
		whitestack = 0;
		blackstack = 0;
		
	}
	
	for (int i = 0; i <= 18; i++) // 세로
	{
		for (int j = 0; j <= 18; j++)
		{
			if (p.pos[i][j] == 1)
			{
				blackstack++;
				whitestack = 0;
			}
			else if (p.pos[i][j] == 2)
			{
				blackstack = 0;
				whitestack++;
			}
			else {
				whitestack = 0;
				blackstack = 0;
			}
			if (blackstack == 5) return 5;
			if (whitestack == 5) return 6;
		}
		whitestack = 0;
		blackstack = 0;
	}

	for (int i = 19; i > 4; i--) // 대각선 ↘
	{
		k = i;
		while (k > 0)
		{
			if (p.pos[19 - k][i - k] == 1)
			{
				blackstack++;
				whitestack = 0;
			}
			else if (p.pos[19 - k][i - k] == 2)
			{
				blackstack = 0;
				whitestack++;
			}
			else {
				whitestack = 0;
				blackstack = 0;
			}
			if (blackstack == 5) return 5;
			if (whitestack == 5) return 6;
			k--;
		}
		whitestack = 0;
		blackstack = 0;
		k = i;
		while (k > 0)
		{
			if (p.pos[i - k][19 - k] == 1)
			{
				blackstack++;
				whitestack = 0;
			}
			else if (p.pos[i - k][19 - k] == 2)
			{
				blackstack = 0;
				whitestack++;
			}
			else {
				whitestack = 0;
				blackstack = 0;
			}
			if (blackstack == 5) return 5;
			if (whitestack == 5) return 6;
			k--;
		}
		whitestack = 0;
		blackstack = 0;
		k = i;
		while (k >= 0) // 대각선 반대
		{
			if (p.pos[k][i - k] == 1)
			{
				blackstack++;
				whitestack = 0;
			}
			else if (p.pos[k][i - k] == 2)
			{
				blackstack = 0;
				whitestack++;
			}
			else {
				whitestack = 0;
				blackstack = 0;
			}
			if (blackstack == 5) return 5;
			if (whitestack == 5) return 6;
			k--;
		}
		whitestack = 0;
		blackstack = 0;
		k = i;
		while (k > 0)
		{
			if (p.pos[k - i + 19][19 - k] == 1)
			{
				blackstack++;
				whitestack = 0;
			}
			else if (p.pos[k - i + 19][19 - k] == 2)
			{
				blackstack = 0;
				whitestack++;
			}
			else {
				whitestack = 0;
				blackstack = 0;
			}
			if (blackstack == 5) return 5;
			if (whitestack == 5) return 6;
			k--;
		}
		whitestack = 0;
		blackstack = 0;
	}
	if (p.pos[p.xpos][p.ypos] != 0) // 이미 둔곳
	{
		return 1;
	}
	return 0;
}

void sysText(xycoord p, int k)
{
	movetoxy(50, 10);
	switch (k)
	{
	case 0:
	{
		std::cout << "　　　　　　　　　";
		break;
	}
	case 1:
	{
		std::cout << "이미 둔곳입니다. ";// 이미 둔 곳
		break;
	}
	case 2:
	{
		std::cout << "33입니다. ";
		break;
	}
	case 3:
	{

		std::cout << "44입니다. ";
		break;
	}
	case 4:
	{
		std::cout << "6목입니다. ";
		break;
	}
	case 5:
	{
		std::cout << "흑 승! ";
		break;
	}
	case 6:
	{
		std::cout << "백 승! ";
		break;
	}

	}
	movetoxy(p.xpos * 2, p.ypos);

}


void startscreen()
{
	movetoxy(0, 0);
	std::cout << "반갑습니다. 아무키나 누르세요. ";
	movetoxy(5, 1);
	std::cout << "○ = 흑, ● = 백";
	movetoxy(0, 2);
	std::cout << "흑은 33, 44, 6목이 금지됩니다.";
	anyKey();
}

void tableOverlay()
{
	clearScreen();

	for (int i = 0; i < 19; i++)
	{
		movetoxy(0, i);
		std::cout << "┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼";
	};
	movetoxy(18, 9);
	std::cout << "※";
}

char anyKey()
{
	char pressed;
	pressed = _getch();
	return pressed;
}

void movetoxy(int col, int row)

{

	COORD position = { tableXpos + col - 1, tableYpos + row - 1 };    // 오목판 위치만큼 movetoxy가 가는위치도 변함

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

}

void clearScreen()
{
	system("cls");
}
