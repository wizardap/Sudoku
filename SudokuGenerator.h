#ifndef SUDOKUGENERATOR__H_
#define SUDOKUGENERATOR__H_

#include<iostream>
#include<algorithm>
#include<random>
#include<chrono>
#include<windows.h>
#include<thread>
#include <cstdlib>


class SudokuGenerator
{
    static constexpr int NUM_ROWS = 9;
    static constexpr int NUM_COLS = 9;
    static constexpr int UNASSIGNED = 0;
    int grid[9][9];
    int answer_grid[9][9];
    bool SUCCESS_FILLED =false;
    static constexpr int TIME_DELAYED = 500;// milliseconds


public:
    SudokuGenerator();
    virtual ~SudokuGenerator();
    void printPuzzle();
    void printAnswerPuzzle();
    bool fillPuzzle();
    void generatePuzzle(int difficulty);
    bool solvePuzzle(bool simulation);
    bool checkSolution();
    void clearConsole();
    bool changeValue(int row,int col,int number);
    bool isFull();
    void delay(int seconds);
    int get(int x,int y);
    int getAnswer(int x,int y);
private:
    void gotoXY(int X,int Y);
    bool fillRemainingBox();
    void fillDiagionalBox(int boxStartRow,int boxStartCol);
    bool usedInRow(const int &value,int row);
    bool usedInColumn(const int &value,int col);
    bool usedInBox(const int &value,int boxStartRow,int boxStartCol);
    bool isSafe(int value,int row,int col);
    bool FindEmptyCoordinate(int &row,int &col);
    int countSolutions();

};

#endif // SUDOKUGENERATOR__H_
