#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <time.h>
#include <cctype>
#include <vector>

using namespace std;

void tic_tac_toe_run();
void snake_game_run();
void hangman_run();

int main()
{
    srand(time(0));
    int choice;
    do
    {
        system("cls");
        cout << "=======================" << endl;
        cout << "      GAME MENU        " << endl;
        cout << "=======================" << endl;
        cout << "1. Tic Tac Toe" << endl;
        cout << "2. Snake" << endl;
        cout << "3. Hangman" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            tic_tac_toe_run();
            break;
        case 2:
            snake_game_run();
            system("pause");
            break;
        case 3:
            system("cls");
            hangman_run();
            break;
        case 4:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            system("pause");
        }
    } while (choice != 4);

    return 0;
}
