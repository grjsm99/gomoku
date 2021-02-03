
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

void movetoxy(int xpos, int ypos);
void clearScreen();
char anyKey();
void startscreen();
void tableOverlay();
int GameControl(xycoord* p, int* i);
int checkPos(xycoord p);
void sysText(xycoord p, int k);


int main(void)
{
	int win=0;
	startscreen();
	xycoord dpos{ { 0 }, 9, 9, false }; // 중앙
	tableOverlay();
	movetoxy(dpos.xpos * 2, dpos.ypos );
	GameControl(&dpos, &win);

	if (win == 1) sysText(dpos, win+4);

		movetoxy(0, 0);
	std::cout << "게임 끝!";

	anyKey();
	



}

int GameControl(xycoord* p, int *i)
{
	int check=0;
	char keybuff;
	while (1)
	{
		if (checkPos(*p) == 5) return 1;  // 흑승
		if (checkPos(*p) == 6) return 2; // 백승
		keybuff = 0;
		while (keybuff != 32)
		{

			switch (keybuff = anyKey())
			{
			case (LEFT):
			{
				if (p->xpos != 0) p->xpos--;
				break;
			}

			case (RIGHT):
			{
				if (p->xpos != 18) p->xpos++;
				break;
			}

			case (DOWN):
			{
				if (p->ypos != 18) p->ypos++;
				break;
			}

			case (UP):
			{	
				if (p->ypos != 0) p->ypos--;
				break;
			}
			}
			movetoxy(p->xpos * 2, p->ypos);
		}
		check = checkPos(*p);

		if (check == 0 && p->borw == false) p->pos[p->xpos][p->ypos] = 1; // 흑=1, 백=20, 돌이 없을때만 둠
		else if (check == 0 && p->borw == true) p->pos[p->xpos][p->ypos] = 20;
		else
		{
			sysText(*p, check); // 돌이있을경우 출력후 다시 돌아감
			continue;
		}
		if (check == 5) return 0;

		if (p->borw == false) // 흑일때, 
		{
			std::cout << "○";
			p->borw = true; // 백턴으로
		}
		else
		{
			std::cout << "●";
			p->borw = false;
		}
		sysText(*p, 0); // 지우기
		
	}
	
}

int checkPos(xycoord p) // 
{
	int count = 0;
	int k = 0;

	if (p.pos[p.xpos][p.ypos] != 0) // 이미 둔곳
	{	
		return 1;
	}

	if (p.borw == true) 
	{
		for (int i = 0; i < 19; i++) // 흑 가로축 승리조건
		{
			for (int j = 0; j < 19; j++)
			{ 
				count += p.pos[j][i]; // 00 10 20
				if (p.pos[j][i] != 1) count = 0;
				if (count == 5) return 5; // 흑승
			}
			count = 0;
		}

		for (int i = 0; i < 19; i++) // 흑 세로축 승리조건
		{
			for (int j = 0; j < 19; j++)
			{
				count += p.pos[i][j];
				if (p.pos[i][j] != 1) count = 0;
				if (count == 5) return 5; // 흑승
			}
			count = 0;
		}

// 흑 대각선 ↘

		for (int i = 19; i > 4; i--)
		{
			k = i;
			while (k > 0)
			{
				count += p.pos[19 - k][i - k];
				if (p.pos[19 - k][i - k] != 1) count = 0;
				if (count == 5) return 5;
				k--;
			}
			count = 0;
			k = i;

			while (k > 0)
			{
				count += p.pos[i - k][19 - k]; 
				if (p.pos[i - k][19 - k] != 1) count = 0;
				if (count == 5) return 5;
				k--;
			}
			count = 0;
			k = i;

// 흑 대각선 ↙
			while (k > 0)
			{
				count += p.pos[k][i - k];
				if (p.pos[k][i - k] != 1) count = 0;
				if (count == 5) return 5;
				k--;
			}
			count = 0;
			k = i;

			while (k > 0)
			{
				count += p.pos[k - i + 19][19 - k];
				if (p.pos[k - i + 19][19 - k] != 1) count = 0;
				if (count == 5) return 5;
				k--;
			}
			count = 0;
		}


	} 
	if (p.borw == false)
	{
		for (int i = 0; i < 19; i++) // 흑 가로축 승리조건
		{
			for (int j = 0; j < 19; j++)
			{
				count += p.pos[j][i];
				if (p.pos[j][i] != 20) count = 0;
				if (count == 100) return 6; // 백승
			}
			count = 0;
		}

		for (int i = 0; i < 19; i++) // 백 세로축 승리조건
		{
			for (int j = 0; j < 19; j++)
			{
				count += p.pos[i][j];
				if (p.pos[i][j] != 20) count = 0;
				if (count == 100) return 6; // 백승
			}
			count = 0;
		}
	}

	return 0;
	 
}

void sysText(xycoord p, int k)
{
	movetoxy(50, 10);
	//std::cout << "count =" << count;
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
	movetoxy(0,0);
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
		movetoxy(0,i);
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
