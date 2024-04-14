#include <iostream>
#include <conio.h>
#include <Windows.h>

class Snake
{
	//todo �첿�� ����

private:
	int width;	//! ���� ���� �ʺ�
	int height;	//! ���� ���� ����

	int snakeX; //! �� �Ӹ� ��ġ 
	int snakeY;

	int fruitX; //! ���� ��ġ
	int fruitY;

	int* tailX; //! �� ���� ��ġ
	int* tailY;

	int nTail;	//! ���� ����

	enum eDirection
	{
		STOP = 0, LEFT, RIGHT, UP, DOWN //! �� ����
	};
	eDirection dir;

public:
	int score; //! ����

	Snake(int w, int h) :
		width(w), height(h), snakeX(w / 2), snakeY(h / 2),
		fruitX(rand() % w), fruitY(rand() % h),
		score(0), nTail(STOP)
	{
		tailX = new int(width * height);
		tailY = new int(width * height);
	}
	~Snake()
	{
		delete[] tailX;
		delete[] tailY;
	}

	void Draw();
	void Input();
	void Login();
};

void Snake::Draw()
{
	//! ��� �� �׸��� ����
	for (int i = 0; i < width + 2; ++i)
	{
		std::cout << '#';
	}
	std::cout << std::endl;

	//! ���� ���� �׸���
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (j == 0)
				std::cout << '#';

			if (i == snakeY && j == snakeX)
				std::cout << '0';
			else if (i == fruitY && j == fruitX)
				std::cout << 'F';
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; ++k)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
					std::cout << " ";
			}
			if (j == width - 1)
				std::cout << '#'; //! ������ ��
		}
		std::cout << std::endl;
	}
	//! �ϴ� �� �׸��⿵��
	for (int i = 0; i < width + 2; ++i)
	{
		std::cout << '#';
	}
	std::cout << std::endl;
	std::cout << "Score :" << score << std::endl;
}

void Snake::Input()
{
	if (_kbhit()) //! Ű���� �Է��� ������ 
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			dir = STOP;
			break;
		case 'q':
			exit(0);
			break;
		}
	}
}

void Snake::Login()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = snakeX;
	tailY[0] = snakeY;

	for (int i = 1; i < nTail; ++i)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case Snake::LEFT:
		--snakeX;
		break;
	case Snake::RIGHT:
		++snakeX;
		break;
	case Snake::UP:
		--snakeY;
		break;
	case Snake::DOWN:
		++snakeY;
		break;
	default:
		break;
	}

	if (snakeX >= width || snakeX < 0 || snakeY >= height || snakeY < 0)
	{
		exit(0); //! ���� �ε����� ���� ����
	}

	for (int i = 0; i < nTail; ++i)
	{
		if (tailX[i] == snakeX && tailY[i] == snakeY)
		{
			exit(0); //! ���� ���� �ε����� ���� ����
		}
	}

	if (snakeX == fruitX && snakeY == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		++nTail;
	}
}

class Game
{
private:
	int width;
	int height;
	Snake* snake;

public:
	Game(int w, int h) : width(w), height(h)
	{
		snake = new Snake(width, height);
	}

	~Game()
	{
		delete snake;
	}

	void Run()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(hConsole, &cursorInfo);
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hConsole, &cursorInfo);

		while (1)
		{
			snake->Draw();
			snake->Input();
			snake->Login();
			Sleep(100); //! 0.1�� ���� ������Ʈ ���ּ���
			std::cout << "\033[H\033[J";
		}
		std::cout << "���� ����! ���� ���� :" << snake->score << std::endl;
	};

};


int main()
{
	Game game(20, 20);
	game.Run();
	return 0;
}