#include <iostream>
#include "Game.h"


using namespace std;

Game::Game()
{
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            grid[i][j] = ' ';
        }
    }

    currentTetro = nullptr;
    currentRow = 0;
    currentCol = WIDTH / 2-2;


    cout << "Loading....\n";

}

Game::~Game()
{
    if (currentTetro)
        delete currentTetro;
}

void Game::clearTetromino(const Tetromino& tetro, int row, int col)
{
    for (int i = 0, i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (tetro.shape[i][j] != ' ')
            {
                int x = row + i;
                int y = col`+ j;

                if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH)
                    grid[x][y] = ' ';

            }
        }
    }
}

bool Game::canMove(const Tetromino& tetro, int newRow, int newCol)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (tetro.shape[i][j] != '')
            {
                int x = newRow + i;
                int y = newCol + j;

                                if (x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH)
                    return false;

               
                if (grid[x][y] != ' ' && !(x >= currentRow && x < currentRow + 4 && y >= currentCol && y < currentCol + 4))
                    return false;
            }
        }
    }
    return true;
}

void Game::moveDown()
{
    if (!currentTetro) return;

    if (canMove(*currentTetro, currentRow + 1, currentCol))
    {
        clearTetromino(*currentTetro, currentRow, currentCol);
        currentRow++;
        placeTetromino(*currentTetro, currentRow, currentCol);
    }
    else
    {
       
        delete currentTetro;
        currentTetro = new Tetromino('T');
        currentRow = 0;
        currentCol = WIDTH / 2 - 2;

        placeTetromino(*currentTetro, currentRow, currentCol);
    }
}


void Game::run()
{
    cout << "Game Started\n";

    Tetromino t('T');
    placeTetromino(t, 0, 3);
    draw();

}

void Game::draw()
{
    system("cls");

    cout << "+------------+\n";
    
    for (int i = 0; i < HEIGHT; ++i)
    {
        cout << "|";
        for (int j = 0; j < WIDTH; ++j)
        {
            cout << grid[i][j];

        }
        cout << "|\n";
    }

    cout << "+------------+\n";
}


void Game::placeTetromino(const Tetromino& tetro, int row, int col)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (tetro.shape[i][j] != ' ')
            {
                int x = row + i;
                int y = col + j;

                if (x >= 0 && x < HEIGHT && y >= 0 && < WIDTH)
                {
                    grid[x][y] = tetro.shape[i][j];

                }

            }
        }
    }
}
