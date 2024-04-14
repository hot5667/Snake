#include <iostream>
#include <conio.h>
#include <Windows.h>

class Snake
{
	//todo 뱀꼬리 게임

private:
	int width;	//! 게임 영역 너비
	int height;	//! 게임 영역 높이

	int snakeX; //! 뱀 머리 위치 
	int snakeY;

	int fruitX; //! 먹이 위치
	int fruitY;

	int* tailX; //! 뱀 꼬리 위치
	int* tailY;

	int nTail;	//! 꼬리 길이

	enum eDirection
	{
		STOP = 0, LEFT, RIGHT, UP, DOWN //! 뱀 방향
	};
	eDirection dir;

public:
	int score; //! 점수

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
	//! 상단 벽 그리는 영역
	for (int i = 0; i < width + 2; ++i)
	{
		std::cout << '#';
	}
	std::cout << std::endl;

	//! 게임 영역 그리기
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
				std::cout << '#'; //! 오른쪽 벽
		}
		std::cout << std::endl;
	}
	//! 하단 벽 그리기영역
	for (int i = 0; i < width + 2; ++i)
	{
		std::cout << '#';
	}
	std::cout << std::endl;
	std::cout << "Score :" << score << std::endl;
}

void Snake::Input()
{
	if (_kbhit()) //! 키보드 입력이 있으면 
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
		exit(0); //! 벽에 부딪히면 게임 종료
	}

	for (int i = 0; i < nTail; ++i)
	{
		if (tailX[i] == snakeX && tailY[i] == snakeY)
		{
			exit(0); //! 뱀의 몸에 부딪히면 게임 종료
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
			Sleep(100); //! 0.1초 마다 업데이트 해주세요
			std::cout << "\033[H\033[J";
		}
		std::cout << "게임 오버! 최종 점수 :" << snake->score << std::endl;
	};

};


int main()
{
	Game game(20, 20);
	game.Run();
	return 0;
}