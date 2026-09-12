#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, TOP, BOTTOM };
Direction dir_snake;

const int height_s = 20;
const int width_s = 25;
int headx, heady, fruitx, fruity, score_s = 0;
int tail_length = 0;
int tailx[100];
int taily[100];
bool game_over_s;

void snake_setup()
{
    game_over_s = false;
    dir_snake = STOP;
    headx = width_s / 2;
    heady = height_s / 2;
    fruitx = rand() % width_s;
    fruity = rand() % height_s;
    score_s = 0;
    tail_length = 0;
}

void snake_draw()
{
    system("cls");
    for (int i = 0; i < width_s + 2; i++) cout << "#";
    cout << endl;

    for (int y = 0; y < height_s; y++)
    {
        for (int x = 0; x < width_s; x++)
        {
            if (x == 0) cout << "#";
            if (headx == x && heady == y) cout << "O";
            else if (fruitx == x && fruity == y) cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < tail_length; k++)
                {
                    if (tailx[k] == x && taily[k] == y)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
            if (x == width_s - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width_s + 2; i++) cout << "#";
    cout << endl;
    cout << "Score: " << score_s << endl;
}

void snake_input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a': dir_snake = LEFT; break;
        case 'w': dir_snake = TOP; break;
        case 's': dir_snake = BOTTOM; break;
        case 'd': dir_snake = RIGHT; break;
        case 'e': game_over_s = true; break;
        }
    }
}

void snake_logic()
{
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X, prev2Y;
    tailx[0] = headx;
    taily[0] = heady;
    for (int i = 1; i < tail_length; i++)
    {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir_snake)
    {
    case TOP: heady--; break;
    case BOTTOM: heady++; break;
    case LEFT: headx--; break;
    case RIGHT: headx++; break;
    default: break;
    }

    if (headx >= width_s) headx = 0; else if (headx < 0) headx = width_s - 1;
    if (heady >= height_s) heady = 0; else if (heady < 0) heady = height_s - 1;

    if (headx == fruitx && heady == fruity)
    {
        score_s += 10;
        fruitx = rand() % width_s;
        fruity = rand() % height_s;
        tail_length++;
    }

    for (int i = 0; i < tail_length; i++)
        if (tailx[i] == headx && taily[i] == heady)
            game_over_s = true;
}

void snake_game_run()
{
    snake_setup();
    while (!game_over_s)
    {
        snake_draw();
        snake_input();
        snake_logic();
        Sleep(50);
    }

    ofstream out("snake_game_data.txt", ios::app);
    if (out) out << score_s << endl;
    out.close();
}
