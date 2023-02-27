#include "Sudoku.h"
#include <string>
void encodeString(string &s)
{
    while (s[0] == ' ')
        s.erase(0, 1);
    while (s.back() == ' ')
        s.erase((int)s.size() - 1, 1);
    for (int i = 0; i + 1 < int(s.size());)
        if (s[i] == ' ' && s[i + 1] == ' ')
            s.erase(i, 1);
        else
            i++;
    for (char &character : s)
    {
        if (character >= 'a' && character <= 'z')
            character -= 32;
    }
}
int main(int argc, char *argv[])
{
    Sudoku Table;
    cout << "Please open the full-screen mode to improve your experience!\n";
    cout << "This game have 2 operations :\n";
    cout << "+) Give up : Input the string \"GIVE UP\" to give up and show the one of all solutions\n";
    cout << "+) X Y Z: X is the 1-based X-coordinate , Y is the 1-based Y-coordinate and Z is the value you wanna put (1..9).\n\t (X,Y is the coordinate which you wanna put your value)\n";
    char ok;
    cout << "Are you ready ? (Y/N)";
    cin >> ok;
    if (ok == 'N' || ok == 'n')
    {
        cout << "Ok ! See you next time!";
        return 0;
    }
    cout << "Great! Let's start\n";
    Table.clearConsole();

    while (true)
    {
        cout << "Choose your difficulty from 5 to 64:";
        int difficulty;
        cin >> difficulty;
        Table.clearConsole();
        Table.generatePuzzle(difficulty);

        bool endGame = false;
        bool giveUp = false;
        cin.ignore();
        while (true)
        {
            Table.printPuzzle();
            cout << endl;
            cout << "Write your operation:";
            string opt;
            getline(cin, opt);
            encodeString(opt);
            if (opt == "GIVE UP")
            {
                giveUp = true;
                break;
            }
            opt += ' ';
            int number[3] = {-1};
            int nums = 0;
            int tmp = 0;
            bool invalid_opt = false;
            for (int id = 0; id < (int)opt.size(); id++)
            {
                char &character = opt[id];
                if (character == '-')
                {
                    invalid_opt = true;
                    break;
                }
                if (character >= '0' && character <= '9')
                {
                    tmp = tmp * 10 + character - '0';
                }
                else
                {
                    if (nums == 3)
                    {
                        invalid_opt = true;
                        break;
                    }
                    number[nums] = tmp;
                    nums++;

                    tmp = 0;
                }
            }
            if (invalid_opt || (nums != 3))
            {
                cout << "Invalid number! Try again";
                Table.delay(1000);
                Table.clearConsole();
                continue;
            }
            for (int id = 0; id < nums; id++)
                if (!(number[id] >= 1 && number[id] <= 9))
                {
                    invalid_opt = false;
                    break;
                }
            if (invalid_opt)
            {
                cout << "Invalid number! Try again";
                Table.delay(1000);
                Table.clearConsole();
                continue;
            }
            if (!Table.changeValue(number[0] - 1, number[1] - 1, number[2]))
            {
                if (Table.isFull())
                {
                    endGame = true;
                    break;
                }
                cout << "Cannot put this value to that coordinate! Please try again!";
                Table.delay(2000);
                Table.clearConsole();
            }
            else
            {
                if (Table.isFull())
                {
                    endGame = true;
                    break;
                }
                Table.clearConsole();
            }
        }
        if (giveUp)
        {
            Table.printAnswerPuzzle();
            cout << endl;
            cout << "Next game ?(Y/N) ";
            char ok;
            cin >> ok;
            if (ok == 'N' || ok == 'n')
            {
                cout << "See you soon!";
                break;
            }
            else
            {
                Table.clearConsole();
                continue;
            }
        }
        if (endGame)
        {
            cout << "You are so intelligent! Do you wanna play one more time ? (Y/N) : ";
            char ok;
            cin >> ok;
            if (ok == 'N' || ok == 'n')
            {
                cout << "See you soon!";
                break;
            }
            else
            {
                Table.clearConsole();
                continue;
            }
        }
    }

    return 0;
}
