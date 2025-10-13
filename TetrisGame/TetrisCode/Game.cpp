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

    cout << "Loading....\n";

}


void Game::run()
{
    cout << "Game Started\n";
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