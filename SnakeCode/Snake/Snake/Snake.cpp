#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
int foodX, foodY;

void DrawEmptyBoard()
{
    system("cls");

    for (int i = 0;i < HEIGHT;i++)
    {
        for (int j = 0;j < WIDTH;j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
            {
                cout << "#";
            }
            else
            {
                cout << " ";
            }
        }
        cout << "\n";
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




void drawBoard(Snake& snake, int foodX, int foodY)
{
    system("cls");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            bool printed = false;

            for (int k = 0; k < snake.getLength();k++)
            {
                if (snake.getX(k) == j && snake.getY(k) == i)
                {
                    if (k == 0) cout << "O";
                    else cout << "o";
                    printed = true;
                    break;
                }
            }

            if (!printed && j == foodX && i == foodY)
            {
                cout << "*";
                printed = true;
            }

            if (!printed)
            {
                if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                {
                    cout << "#";

                }else
                {
                    cout << " ";
                }
            }
        }
        cout << "\n";
    }
}

void input(int& dx, int& dy)
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w': dx = 0; dy = -1; break;
        case 's': dx = 0; dy = 1; break;
        case 'a': dx = -1; dy = 0; break;
        case 'd': dx = 1; dy = 0; break;
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



int main()
{
    srand(time(0));
    Snake snake;
    int dx = 0;
    int dy = 0;
    bool gameOver = false;

    spawnFood();

    while (!gameOver)
    {
        drawBoard(snake,foodX,foodY);
        input(dx, dy);
        if (dx != 0 || dy != 0)
        {
            snake.move(dx, dy);
            if (snake.getX(0) == foodX && snake.getY(0) == foodY)
            {
                snake.grow();
                spawnFood();
            }
        }
        if (hitWall(snake))
        {
            gameOver = true;
        }

        if (snake.isColliding())
        {
            gameOver = true;
        }


        Sleep(180);
    }
    cout << "GAME OVER! Scor: " << snake.getLength() - 1 << "\n";
    return 0;
}