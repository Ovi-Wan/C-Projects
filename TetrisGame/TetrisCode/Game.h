#include "Tetromino.h"
#ifndef GAME_H
#define GAME_H

const int WIDTH = 10;
const int HEIGHT = 20;


class Game
{
    private:
        char grid[HEIGHT][WIDTH];


        Tetromino* currentTetro;
        int currentRow, currentCol;


    public:
        Game();
        ~Game();

        void run();
        void draw();

        void placeTetromino(const Tetromino& tetro, int row, int col);
        void clearTetromino(const Tetromino& tetro, int row, int col);
        void canMove(const Tetromino& tetro, int newRow, int newCol);

        void moveDown();
};


#endif
