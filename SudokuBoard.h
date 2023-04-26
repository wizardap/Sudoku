#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include "SudokuCell.h"
#include "SudokuBoard.h"
#include "SudokuGenerator.h"
#include<map>

class SudokuBoard
{
public:
    SudokuBoard();
    virtual ~SudokuBoard();
    void draw(SDL_Renderer* SDK_Renderer,bool draw_answer=false);
    void update(SDL_Event e);
    void setDifficulty(int difficulty);
    SudokuCell* checkRow(SudokuCell *cell,int row);
    SudokuCell* checkCol(SudokuCell *cell,int col);
    SudokuCell* checkInBox(SudokuCell *cell,int row,int col);

protected:

private:
    SudokuGenerator generator;
    SudokuCell grid[9][9];
    SudokuCell* selectedCell;
    std::map<SudokuCell*,std::vector<SudokuCell*>> wrong_cell;
};

#endif // SUDOKUBOARD_H
