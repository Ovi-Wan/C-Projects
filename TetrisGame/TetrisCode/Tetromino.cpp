#include <iostream>
#include "Tetromino.h"
#include <cstring>


using namespace std;


Tetromino::Tetromino(char type)
{

    cout << "Game Created\n";

    for(int i = 0; i < 4; ++i)
        for (int j = 0; j <4; ++j)
            shape[i][j] = ' ';


    switch(type)
    {
        case 'I':
            shape [1][0] = 'I';
            shape [1][1] = 'I';
            shape [1][2] = 'I';
            shape [1][3] = 'I';
            break;
        case 'O':
            shape [1][1] = 'O';
            shape [1][2] = 'O';
            shape [2][1] = 'O';
            shape [2][2] = 'O';
            break;
        case 'T':
            shape [1][0] = 'T';
            shape [1][1] = 'T';
            shape [1][2] = 'T';
            shape [2][1] = 'T';
            break;
        case 'L':
            shape [1][0] = 'L';
            shape [2][0] = 'L';
            shape [3][0] = 'L';
            shape [3][1] = 'L';
            break;
        case 'J':
            shape [1][1] = 'J';
            shape [2][1] = 'J';
            shape [3][1] = 'J';
            shape [3][0] = 'J';
            break;
        case 'S':
            shape [1][1] = 'S';
            shape [1][2] = 'S';
            shape [2][0] = 'S';
            shape [2][1] = 'S';
            break;
        case 'Z':
            shape [1][0] = 'Z';
            shape [1][1] = 'Z';
            shape [2][1] = 'Z';
            shape [2][2] = 'Z';
            break;
        default:
            break;

    }
    
}
