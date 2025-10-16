#ifndef GAME_H
#define GAME_H

const int WIDTH = 10;
const int HEIGHT = 20;


class Game
{
    private:
        char grid[HEIGHT][WIDTH];

    public:
        Game();
        void run();
        void draw();

};


#endif