#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <windows.h>

using namespace std;

void drawblock_h(string msg, bool top = false, bool bottom = false)
{
    if (top) cout << "+-----------------------------------+" << endl;
    cout << "|";
    bool front = true;
    for (int i = msg.length(); i < 35; i++)
    {
        if (front) msg = " " + msg;
        else msg = msg + " ";
        front = !front;
    }
    cout << msg << "|" << endl;
    if (bottom) cout << "+-----------------------------------+" << endl;
}

void drawhangman(int guess = 0)
{
    if (guess >= 0) drawblock_h("HangMan", true, true);
    if (guess >= 1) drawblock_h("|"); else drawblock_h("");
    if (guess >= 2) drawblock_h("|"); else drawblock_h("");
    if (guess >= 3) drawblock_h("O"); else drawblock_h("");
    if (guess >= 4) drawblock_h("|"); else drawblock_h("");
    if (guess == 5) drawblock_h("/");
    if (guess == 6) drawblock_h("/|");
    if (guess >= 7) drawblock_h("/ | \\"); else drawblock_h("");
    if (guess >= 8) drawblock_h("|"); else drawblock_h("");
    if (guess == 9) drawblock_h("/");
    if (guess == 10) drawblock_h("/|");
    if (guess >= 11) drawblock_h("/ | \\");
}

void printletters(string input, char from, char to)
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos) { s += i; s += " "; }
        else { s += "  "; }
    }
    drawblock_h(s);
}

void print_available_letters(string taken)
{
    drawblock_h("Available Letters", true, true);
    printletters(taken, 'A', 'M');
    printletters(taken, 'N', 'Z');
}

bool print_word_check_win(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos) { s += "_"; won = false; }
        else { s += word[i]; s += " "; }
    }
    drawblock_h(s, true, true);
    return won;
}

string load_random_words(string path)
{
    ifstream in(path, ios::in);
    vector<string> word_store;
    string line;
    if (in.is_open())
    {
        while (getline(in, line)) word_store.push_back(line);
        in.close();
        if (!word_store.empty()) return word_store[rand() % word_store.size()];
    }
    return "PROGRAM"; 
}

int tries_left(string word, string guessed)
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++)
        if (word.find(guessed[i]) == string::npos) error++;
    return error;
}

void hangman_run()
{
    string word_to_guess = load_random_words("hangman_words.txt");
    string guesses = "";
    int tries = 0;
    bool win_h = false;
    do
    {
        system("cls");
        drawhangman(tries);
        print_available_letters(guesses);
        drawblock_h("Guess the word");
        win_h = print_word_check_win(word_to_guess, guesses);

        if (win_h) break;

        char x;
        cout << ">";
        cin >> x;
        x = toupper(x);

        if (guesses.find(x) == string::npos) guesses += x;
        tries = tries_left(word_to_guess, guesses);

    } while (tries <= 11);

    if (win_h) drawblock_h("YOU WON!", false, true);
    else drawblock_h("GAME OVER", true, true);
    drawblock_h("THE WORD WAS: " + word_to_guess, false, true);

    system("pause");
}
