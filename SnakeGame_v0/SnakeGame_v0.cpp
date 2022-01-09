#include <iostream>
#include <conio.h>			//console input output, has 2 asynhronus functions that dont blok program
#include <Windows.h>
using namespace std;

bool GameOver;

const int Screen_Width = 20;
const int Screen_Height = 20;

int Snake_x, Snake_y, Fruit_x, Fruit_y, Score;

int Snake_Tail_x[100], Snake_Tail_y[100];
int Length_Tail;

enum SnakeDirection { Stop = 0, Left, Right, Up, Down };

SnakeDirection dir;

void Setup()
{
	GameOver = false;
	dir = Stop;
	Snake_x = Screen_Width / 2;
	Snake_y = Screen_Height / 2;

	Fruit_x = rand() % Screen_Width;
	Fruit_y = rand() % Screen_Height;

	Score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < Screen_Width + 2; i++)
		cout << "#";

	cout << endl;

	for (int i = 0; i < Screen_Height; i++)
	{
		for (int j = 0; j < Screen_Width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == Snake_y && j == Snake_x)
				cout << "O";
			else if (i == Fruit_y && j == Fruit_x)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < Length_Tail; k++)
				{
					if (Snake_Tail_x[k] == j && Snake_Tail_y[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == Screen_Width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < Screen_Width + 2; i++)
		cout << "#";

	cout << endl;

	cout << "Score: " << Score << endl;

}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 'w':
			dir = Up;
			break;
		case 's':
			dir = Down;
			break;
		case 'x':
			GameOver = true;
			break;

		}
	}
}

void Logic()
{
	int prev_Tail_position_x = Snake_Tail_x[0];
	int prev_Tail_position_y = Snake_Tail_y[0];
	int prev_Tail_position_2x, prev_Tail_position_2y;

	Snake_Tail_x[0] = Snake_x;
	Snake_Tail_y[0] = Snake_y;

	for (int i = 1; i < Length_Tail; i++)
	{
		prev_Tail_position_2x = Snake_Tail_x[i];
		prev_Tail_position_2y = Snake_Tail_y[i];

		Snake_Tail_x[i] = prev_Tail_position_x;
		Snake_Tail_y[i] = prev_Tail_position_y;

		prev_Tail_position_x = prev_Tail_position_2x;
		prev_Tail_position_y = prev_Tail_position_2y;
	}

	switch (dir)
	{

	case Left:
		Snake_x--;
		break;
	case Right:
		Snake_x++;
		break;
	case Up:
		Snake_y--;
		break;
	case Down:
		Snake_y++;
		break;
	default:
		break;
	}

	//if (Snake_x > Screen_Width - 1 || Snake_x < 0 || Snake_y > Screen_Height - 1 || Snake_y < 0)	//-1 Snake dies before the wall
	//a	GameOver = true;

	if (Snake_x >= Screen_Width)Snake_x = 0; else if (Snake_x < 0)Snake_x = Screen_Width - 1;
	if (Snake_y >= Screen_Height)Snake_y = 0; else if (Snake_y < 0)Snake_y = Screen_Height - 1;
	for (int i = 0; i < Length_Tail; i++)
		if (Snake_Tail_x[i] == Snake_x && Snake_Tail_y[i] == Snake_y)
		{
			GameOver = true;
		}

	if (Snake_x == Fruit_x && Snake_y == Fruit_y)
	{
		Score++;
		Fruit_x = rand() % Screen_Width;
		Fruit_y = rand() % Screen_Height;
		Length_Tail++;
	}

}




int main()
{
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
	}


	return 0;
}