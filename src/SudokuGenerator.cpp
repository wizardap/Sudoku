/*

    Basic Sudoku Generator has written in C++
    Writer : WizardAP

*/

#include "SudokuGenerator.h"
SudokuGenerator::SudokuGenerator()
{
    // Initialize the grid
    for (int row =0; row<NUM_ROWS; row++)
        for (int col=0 ; col<NUM_COLS; col++)
            this->grid[row][col] = UNASSIGNED;
    SUCCESS_FILLED = false;
}
SudokuGenerator::~SudokuGenerator()
{
    for (int row =0; row<NUM_ROWS; row++)
        for(int col=0 ; col<NUM_COLS; col++)
            this->grid[row][col] = UNASSIGNED;
    SUCCESS_FILLED = false;
}

int Seed(int maxLimit)
{
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    return rng()%maxLimit;
}

void SudokuGenerator::delay(int milliseconds)
{
    Sleep(milliseconds);
}
bool SudokuGenerator::usedInRow(const int &value,int row)
{
    for (int col = 0; col<NUM_COLS; col++)
    {
        if (this->grid[row][col] == value) return true;
    }
    return false;
}
bool SudokuGenerator::usedInColumn(const int &value,int col)
{
    for (int row = 0;row<NUM_ROWS; row++)
    {
        if (this->grid[row][col] == value) return true;
    }
    return false;
}

int SudokuGenerator::getAnswer(int x, int y)
{
    return answer_grid[x][y];
}

bool SudokuGenerator::usedInBox(const int &value,int boxStartRow,int boxStartCol)
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
bool SudokuGenerator::isSafe(int value,int row,int col)
{
    return !usedInRow(value,row) &&
           !usedInColumn(value,col) &&
           !usedInBox(value,row - row%3,col - col%3);
}
bool SudokuGenerator::FindEmptyCoordinate(int &row,int &col)
{
    for (row=0; row<NUM_ROWS; row++)
        for (col=0; col<NUM_COLS; col++)
            if (this->grid[row][col] == 0) return true;
    return false;
}
int SudokuGenerator::get(int x,int y)
{
    return this->grid[x][y];
}
void SudokuGenerator::fillDiagionalBox(int boxStartRow,int boxStartCol)
{
    int random_list[9] = {1,2,3,4,5,6,7,8,9};
    std::random_shuffle(random_list,random_list+9,Seed);
    for (int row = 0; row<3; row++)
        for (int col =0; col<3; col++)
        {
            int X = boxStartRow + row;
            int Y = boxStartCol + col;
            this->grid[X][Y] =random_list[row*3 + col];
        }
}
bool SudokuGenerator::fillRemainingBox()
{
    int row,col;
    if (!FindEmptyCoordinate(row,col)) return true;
    int random_list[9] = {1,2,3,4,5,6,7,8,9};
    std::random_shuffle(random_list,random_list+9,Seed);
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
bool SudokuGenerator::fillPuzzle()
{
    for (int coor = 0; coor<9; coor+=3)
        fillDiagionalBox(coor,coor);
    if (fillRemainingBox()) SUCCESS_FILLED = true;
    if (!SUCCESS_FILLED)
    {
        std::cout<<"This generator code is error ! Please fix this as soon asp possible!";
        return false;
    }
    return true;
}
int SudokuGenerator::countSolutions()
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
void SudokuGenerator::gotoXY(int X,int Y)
{
    COORD screen;
    static const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    screen.X = X;
    screen.Y = Y;
    SetConsoleCursorPosition(output,screen);
}
bool SudokuGenerator::solvePuzzle(bool simulation)
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
void SudokuGenerator::generatePuzzle(int difficulty)
{
    for (int row = 0; row<NUM_ROWS; row++)
        for (int col =0; col<NUM_COLS; col++)
            this->grid[row][col] = UNASSIGNED;
    fillPuzzle();

    for (int row = 0 ; row<NUM_ROWS; row++)
        for (int col = 0; col<NUM_COLS; col++)
            this->answer_grid[row][col] = this->grid[row][col];

    while(difficulty >0)
    {
        int row,col;
        do
        {
            row = Seed(9);
            col = Seed(9);
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
bool SudokuGenerator::checkSolution()
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
void SudokuGenerator::printPuzzle()
{
    clearConsole();
    int numberOfUnderlines = 77;
    for (int i = 0; i<numberOfUnderlines; i++)
        std::cout<<"=";
    std::cout<<std::endl;
    for (int row =0; row<NUM_ROWS; row++)
    {
        for (int rowSpaceLines = 0; rowSpaceLines<3; rowSpaceLines++)
        {
            for (int col = 0; col<NUM_COLS; col++)
            {
                if (col % 3==0) std::cout<<'|';
                std::cout<<'|';
                for (int spaces = 0; spaces<7; spaces++)
                    if (spaces == 3 && rowSpaceLines ==1)
                    {
                        if (this->grid[row][col] ==  UNASSIGNED)
                        {
                            std::cout<<' ';
                        }
                        else std::cout<<this->grid[row][col];
                    }
                    else
                        std::cout<<' ';
            }
            std::cout<<"||\n";
        }
        for (int underline =0; underline<numberOfUnderlines; underline++)
            if ((row+1) % 3==0 ) std::cout<<"=";
            else std::cout<<"-";
        std::cout<<std::endl;
        // std::cout.flush();
    }
}
void SudokuGenerator::clearConsole()
{
    system("cls");
}
bool SudokuGenerator::changeValue(int row,int col,int number)
{
    if (isSafe(number,row,col))
    {
        this->grid[row][col] = number;
        return true;
    }
    return false;
}
bool SudokuGenerator::isFull()
{
    for (int row =0; row<NUM_ROWS; row++)
        for (int col =0; col<NUM_COLS; col++)
            if (this->grid[row][col] == UNASSIGNED) return false;
    return true;
}
void SudokuGenerator::printAnswerPuzzle()
{
    clearConsole();
    int numberOfUnderlines = 77;
    for (int i = 0; i<numberOfUnderlines; i++)
        std::cout<<"=";
    std::cout<<std::endl;
    for (int row =0; row<NUM_ROWS; row++)
    {
        for (int rowSpaceLines = 0; rowSpaceLines<3; rowSpaceLines++)
        {
            for (int col = 0; col<NUM_COLS; col++)
            {
                if (col % 3==0) std::cout<<'|';
                std::cout<<'|';
                for (int spaces = 0; spaces<7; spaces++)
                    if (spaces == 3 && rowSpaceLines ==1)
                    {
                        if (this->answer_grid[row][col] ==  UNASSIGNED)
                        {
                            std::cout<<' ';
                        }
                        else std::cout<<this->answer_grid[row][col];
                    }
                    else
                        std::cout<<' ';
            }
            std::cout<<"||\n";
        }
        for (int underline =0; underline<numberOfUnderlines; underline++)
            if ((row+1) % 3==0 ) std::cout<<"=";
            else std::cout<<"-";
        std::cout<<std::endl;
    }
}
