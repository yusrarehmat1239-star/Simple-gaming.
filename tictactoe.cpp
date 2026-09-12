#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

char matrix[3][3] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char player = 'X';
bool win_ttt = false;

void draw_game()
{
    system("cls");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void input_ttt()
{
    int a;
    cout << "Your turn, Enter a number: ";
    cin >> a;
    if (a >= 1 && a <= 9)
    {
        int row = (a - 1) / 3;
        int col = (a - 1) % 3;
        if (matrix[row][col] != 'X' && matrix[row][col] != 'O')
        {
            matrix[row][col] = player;
        }
    }
}

void changeplayer()
{
    if (player == 'X')
        player = 'O';
    else
        player = 'X';
}

bool checkwin_ttt()
{
    
    for (int i = 0; i < 3; i++)
    {
        if ((matrix[i][0] == player && matrix[i][1] == player && matrix[i][2] == player) ||
            (matrix[0][i] == player && matrix[1][i] == player && matrix[2][i] == player))
        {
            return true;
        }
    }
    
    if ((matrix[0][0] == player && matrix[1][1] == player && matrix[2][2] == player) ||
        (matrix[0][2] == player && matrix[1][1] == player && matrix[2][0] == player))
    {
        return true;
    }
    return false;
}

void tic_tac_toe_run() 
{
    win_ttt = false;
    player = 'X';
    char resetMatrix[3][3] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            matrix[i][j] = resetMatrix[i][j];

    while (!win_ttt)
    {
        draw_game();
        input_ttt();
        win_ttt = checkwin_ttt();
        if (win_ttt)
        {
            draw_game();
            cout << "Player " << player << " wins!" << endl;
            break;
        }
        changeplayer();
    }
    system("pause");
}
