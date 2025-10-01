#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

const int WIDTH = 30;
const int HEIGHT = 20;
const int MAX_OBSTACLES = 50;
int obstacleX[MAX_OBSTACLES];
int obstacleY[MAX_OBSTACLES];
int obstacleCount = 0;

int foodX, foodY;

void saveScore(const string& nume, int scor)
{
    ofstream fout("score.txt", std::ios::app);
    if (fout.is_open())
    {
        fout << nume << " - " << scor << " puncte\n";
        fout.close();
    }
}

void showScore()
{
    ifstream fin("score.txt");
    if (fin.is_open())
    {
        string line;
        std::cout << "\n Saved scores:\n";
        while (getline(fin, line))
        {
            std::cout << " " << line << "\n";
        }
        fin.close();
    }
    else
    {
        std::cout << "\nNo saved scores yet!.\n";
    }
}

void clearScreen() {
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}




void DrawEmptyBoard()
{
    system("cls");

    for (int i = 0;i < HEIGHT;i++)
    {
        for (int j = 0;j < WIDTH;j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
            {
                std::cout << "#";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

class Snake
{
private:
    int x[100], y[100];
    int length;

public:
    Snake()
    {
        length = 1;
        x[0] = WIDTH / 2;
        y[0] = HEIGHT / 2;

    }
    int getX(int i)
    {
        return x[i];
    }
    int getY(int i)
    {
        return y[i];
    }
    int getLength()
    {
        return length;
    }
    void grow()
    {
        if (length < 100)
            length++;
    }
    void move(int dx, int dy)
    {
        for (int i = length - 1; i > 0; i--)
        {
            x[i] = x[i - 1];
            y[i] = y[i - 1];
        }
        x[0] += dx;
        y[0] += dy;
    }
    bool isColliding()
    {
        for (int i = 1; i < length; i++)
        {
            if (x[0] == x[i] && y[0] == y[i])
            {
                return true;
            }
        }
        return false;
    }


};




void drawBoard(Snake& snake, int foodX, int foodY, int score, int seconds)
{
    clearScreen();

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            bool printed = false;

            for (int k = 0; k < snake.getLength();k++)
            {
                if (snake.getX(k) == j && snake.getY(k) == i)
                {
                    if (k == 0)
                    {
                            std::cout << "\033[34;42mO\033[0m";
                    }
                    else
                    {
                        std::cout << "\033[34;42mo\033[0m";
                    }
                    printed = true;
                    break;
                }
            }

            if (!printed && j == foodX && i == foodY)
            {
                std::cout << "\033[31;42m*\033[0m";
                printed = true;
            }

            for (int o = 0; o < obstacleCount; o++)
            {
                if (obstacleX[o] == j && obstacleY[o] == i)
                {
                    std::cout << "\033[30;47mX\033[0m";
                    printed = true;
                    break;
                }
            }

            if (!printed)
            {
                if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                {
                    std::cout << "\033[37m#\033[0m";

                }
                else
                {
                    std::cout << "\033[32;42m \033[0m";
                }
            }
        }

        if (i == 2) std::cout << "   Controls:";
        if (i == 4) std::cout << "   Move - W A S D";
        if (i == 5) std::cout << "   Pause - P";
        if (i == 6) std::cout << "   Continue - R";
        if (i == 8) std::cout << "   Score:  " << score;
        if (i == 9) std::cout << "   Time:   " << seconds << "  seconds ";
        std::cout << "\n";
    }
}

void input(int& dx, int& dy, bool& paused)
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w': dx = 0; dy = -1; break;
        case 's': dx = 0; dy = 1; break;
        case 'a': dx = -1; dy = 0; break;
        case 'd': dx = 1; dy = 0; break;
        case 'p': paused = true; break;
        case 'r': paused = false; break;
        }
    }
}


bool hitWall(Snake& snake)
{
    int headX = snake.getX(0);
    int headY = snake.getY(0);

    if (headX <= 0 || headX >= WIDTH - 1 || headY <= 0 || headY >= HEIGHT - 1)
    {
        return true;
    }
    return false;
}

void spawnFood()
{
    foodX = rand() % (WIDTH - 2) + 1;
    foodY = rand() % (HEIGHT - 2) + 1;

}

void spawnObstacle(Snake& snake)
{
    if (obstacleCount >= MAX_OBSTACLES) return;

    int x, y;
    bool valid;

    do 
    {
        x = rand() % (WIDTH - 2) + 1;
        y = rand() % (HEIGHT - 2) + 1;
        valid = true;

        for (int i = 0; i < snake.getLength(); i++)
        {
            if (snake.getX(i) == x && snake.getY(i) == y)
            {
                valid = false;
                break;

            }
        }
        if (x == foodX && y == foodY) 
            valid = false;

        for (int i = 0; i < obstacleCount; i++)
        {
            if (obstacleX[i] == x && obstacleY[i] == y)
            {
                valid = false;
                break;
            }
        }
    } while (!valid);
    obstacleX[obstacleCount] = x;
    obstacleY[obstacleCount] = y;
    obstacleCount++;
}

bool hitObstacle(Snake& snake)
{
    for (int i = 0; i < obstacleCount; i++)
    {
        if (snake.getX(0) == obstacleX[i] && snake.getY(0) == obstacleY[i])
        {
            return true;
        }
    }
    return false;
}



int main()
{
    int speed = 180;
    srand(time(0));
    char choice;
    do {


        Snake snake;
        obstacleCount = 0;
        int dx = 0;
        int dy = 0;
        bool gameOver = false;
        bool paused = false;
        time_t startTime = time(0);
        spawnFood();

        while (!gameOver)
        {
            int score = snake.getLength() - 1;
            int seconds = static_cast<int>(difftime(time(0), startTime));
            drawBoard(snake, foodX, foodY, score, seconds);
            if (paused)
                std::cout << "\n⏸ Pauza - apasa 'r' pentru a continua\n";

            input(dx, dy, paused);
            if (!paused && dx != 0 || dy != 0)
            {
                snake.move(dx, dy);
                if (snake.getX(0) == foodX && snake.getY(0) == foodY)
                {
                    snake.grow();
                    spawnFood();

                    if (speed > 50)
                        speed -= 10;

                    int score = snake.getLength() - 1;
                    if (score % 5 == 0 && score <= 75) 
                    {
                        spawnObstacle(snake);
                    }

                }
            }

            if (hitWall(snake))
            {
                gameOver = true;
            }

            if (hitObstacle(snake))
            {
                gameOver = true;
            }

            if (snake.isColliding())
            {
                gameOver = true;
            }


            Sleep(speed);
        }

        std::cout << "GAME OVER! Scor: " << snake.getLength() - 1 << "\n";
        std::cout << "Vrei sa salvezi scorul? (y/n): ";
        char saveChoice;
        std::cin >> saveChoice;

        if (saveChoice == 'y' || saveChoice == 'Y')
        {
            std::string nume;
            std::cout << "Introdu numele tau: ";
            std::cin >> nume;
            saveScore(nume, snake.getLength() - 1);
            showScore();
        }

        std::cout << "Vrei sa joci din nou? (y/n): ";
        std::cin >> choice;
    } while (choice  == 'y' || choice == 'Y');

    return 0;
}