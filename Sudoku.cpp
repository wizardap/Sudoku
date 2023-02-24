/*

    Basic Sudoku Generator has written in C++
    Writer : WizardAP

*/

#include "Sudoku.h"
Sudoku::Sudoku()
{
    // Initialize the grid
    for (int row =0; row<NUM_ROWS; row++)
        for (int col=0 ; col<NUM_COLS; col++)
            this->grid[row][col] = UNASSIGNED;
    SUCCESS_FILLED = false;
}
int Seed(int maxLimit)
{
    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    return rng()%maxLimit;
}
void Sudoku::delay(int milliseconds)
{
    Sleep(milliseconds);
}
bool Sudoku::usedInRow(const int &value,int row)
{
    for (int col = 0; col<NUM_COLS; col++)
    {
        if (this->grid[row][col] == value) return true;
    }
    return false;
}
bool Sudoku::usedInColumn(const int &value,int col)
{
    for (int row = 0; row<NUM_ROWS; row++)
    {
        if (this->grid[row][col] == value) return true;
    }
    return false;
}
bool Sudoku::usedInBox(const int &value,int boxStartRow,int boxStartCol)
{
    for (int row =0; row<3; row++)
        for (int col =0; col<3; col++)
        {
            int X = boxStartRow + row;
            int Y = boxStartCol + col;
            if (this->grid[X][Y] == value) return true;
        }
    return false;
}
bool Sudoku::isSafe(int value,int row,int col)
{
    return !usedInRow(value,row) &&
           !usedInColumn(value,col) &&
           !usedInBox(value,row - row%3,col - col%3);
}
bool Sudoku::FindEmptyCoordinate(int &row,int &col)
{
    for (row=0; row<NUM_ROWS; row++)
        for (col=0; col<NUM_COLS; col++)
            if (this->grid[row][col] == 0) return true;
    return false;
}
int Sudoku::get(int x,int y)
{
    return this->grid[x][y];
}
void Sudoku::fillDiagionalBox(int boxStartRow,int boxStartCol)
{
    int random_list[9] = {1,2,3,4,5,6,7,8,9};
    random_shuffle(random_list,random_list+9,Seed);
    for (int row = 0; row<3; row++)
        for (int col =0; col<3; col++)
        {
            int X = boxStartRow + row;
            int Y = boxStartCol + col;
            this->grid[X][Y] =random_list[row*3 + col];
        }
}
bool Sudoku::fillRemainingBox()
{
    int row,col;
    if (!FindEmptyCoordinate(row,col)) return true;
    int random_list[9] = {1,2,3,4,5,6,7,8,9};
    random_shuffle(random_list,random_list+9,Seed);
    for (int index = 0; index<9; index++)
    {
        int number = random_list[index];
        if (isSafe(number,row,col))
        {
            this->grid[row][col] = number;
            if (fillRemainingBox()) return true;
            this->grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}
void Sudoku::fillPuzzle()
{
    for (int coor = 0; coor<9; coor+=3)
        fillDiagionalBox(coor,coor);
    if (fillRemainingBox()) SUCCESS_FILLED = true;
    if (!SUCCESS_FILLED)
    {
        cout<<"This generator code is error ! Please fix this as soon asp possible!";
        exit(1);
    }
}
int Sudoku::countSolutions()
{
    int row,col;
    if (!FindEmptyCoordinate(row,col)) return 1;
    int solutions =0;
    for (int number = 1; number<=9; number++)
        if (isSafe(number,row,col))
        {
            this->grid[row][col] = number;
            solutions+=countSolutions();
            this->grid[row][col] = UNASSIGNED;
            if (solutions>1) return solutions;
        }
    return solutions;

}
void Sudoku::gotoXY(int X,int Y)
{
    COORD screen;
    static const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    screen.X = X;
    screen.Y = Y;
    SetConsoleCursorPosition(output,screen);
}
bool Sudoku::solvePuzzle(bool simulation)
{
    int row,col;
    if (!FindEmptyCoordinate(row,col)) return true;
    for (int number =1; number<=9; number++)
        if (isSafe(number,row,col))
        {
            this->grid[row][col] = number;
            if (simulation)
            {
                delay(TIME_DELAYED);
                printPuzzle();
            }
            if (solvePuzzle(simulation)) return true;
            this->grid[row][col] = UNASSIGNED;
            if (simulation)
            {
                delay(TIME_DELAYED);
                printPuzzle();
            }
        }
    return false;
}
void Sudoku::generatePuzzle(int difficulty)
{
    for (int row = 0; row<NUM_ROWS; row++)
        for (int col =0; col<NUM_COLS; col++)
            this->grid[row][col] = UNASSIGNED;
    fillPuzzle();

    for (int row = 0 ;row<NUM_ROWS;row++)
        for (int col = 0;col<NUM_COLS;col++)
            this->answer_grid[row][col] = this->grid[row][col];

    while(difficulty >0)
    {
        int row,col;
        do
        {
            row = Seed(8);
            col = Seed(8);
        }
        while(this->grid[row][col] ==UNASSIGNED);
        int tempValue = this->grid[row][col];
        this->grid[row][col] = UNASSIGNED;
        if (countSolutions()!=1)
        {
            this->grid[row][col] = tempValue;
        }
        else difficulty--;
    }
}
bool Sudoku::checkSolution()
{
    for (int row =0; row<NUM_ROWS; row++)
    {
        bool freq[10]= {false};
        for (int col= 0; col<NUM_COLS; col++)
        {
            int value = this->grid[row][col];
            if (freq[value] == true) return false;
            freq[value] = true;
        }
    }

    for (int col=0; col<NUM_COLS; col++)
    {
        bool freq[10] = {false};
        for (int row = 0; row<NUM_ROWS; row++)
        {
            int value = this->grid[row][col];
            if (freq[value] == true)
            {
                return false;
            }
            freq[value] = true;
        }
    }

    for (int boxStartRow = 0; boxStartRow<9; boxStartRow+=3)
        for (int boxStartCol = 0; boxStartCol<9; boxStartCol+=3)
        {
            bool freq[10]= {false};
            for (int row = 0; row<3; row++)
                for (int col =0; col<3; col++)
                {
                    int X = boxStartRow+ row;
                    int Y = boxStartCol + col;
                    int value = this->grid[X][Y];
                    if (freq[value] == true)
                    {
                        return false;
                    }
                    freq[value] = true;
                }

        }

    return true;
}
void Sudoku::printPuzzle()
{
    clearConsole();
    int numberOfUnderlines = 77;
    for (int i = 0; i<numberOfUnderlines; i++)
        cout<<"=";
    cout<<endl;
    for (int row =0; row<NUM_ROWS; row++)
    {
        for (int rowSpaceLines = 0; rowSpaceLines<3; rowSpaceLines++)
        {
            for (int col = 0; col<NUM_COLS; col++)
            {
                if (col % 3==0) cout<<'|';
                cout<<'|';
                for (int spaces = 0; spaces<7; spaces++)
                    if (spaces == 3 && rowSpaceLines ==1)
                    {
                        if (this->grid[row][col] ==  UNASSIGNED)
                        {
                            cout<<' ';
                        }
                        else cout<<this->grid[row][col];
                    }
                    else
                        cout<<' ';
            }
            cout<<"||\n";
        }
        for (int underline =0; underline<numberOfUnderlines; underline++)
            if ((row+1) % 3==0 ) cout<<"=";
            else cout<<"-";
        cout<<endl;
        // cout.flush();
    }
}
void Sudoku::clearConsole()
{
    system("cls");
}
bool Sudoku::changeValue(int row,int col,int number)
{
    if (isSafe(number,row,col))
    {
        this->grid[row][col] = number;
        return true;
    }
    return false;
}
bool Sudoku::isFull()
{
    for (int row =0;row<NUM_ROWS;row++)
        for (int col =0;col<NUM_COLS;col++)
        if (this->grid[row][col] == UNASSIGNED) return false;
    return true;
}
void Sudoku::printAnswerPuzzle()
{
    clearConsole();
    int numberOfUnderlines = 77;
    for (int i = 0; i<numberOfUnderlines; i++)
        cout<<"=";
    cout<<endl;
    for (int row =0; row<NUM_ROWS; row++)
    {
        for (int rowSpaceLines = 0; rowSpaceLines<3; rowSpaceLines++)
        {
            for (int col = 0; col<NUM_COLS; col++)
            {
                if (col % 3==0) cout<<'|';
                cout<<'|';
                for (int spaces = 0; spaces<7; spaces++)
                    if (spaces == 3 && rowSpaceLines ==1)
                    {
                        if (this->answer_grid[row][col] ==  UNASSIGNED)
                        {
                            cout<<' ';
                        }
                        else cout<<this->answer_grid[row][col];
                    }
                    else
                        cout<<' ';
            }
            cout<<"||\n";
        }
        for (int underline =0; underline<numberOfUnderlines; underline++)
            if ((row+1) % 3==0 ) cout<<"=";
            else cout<<"-";
        cout<<endl;
    }
}
