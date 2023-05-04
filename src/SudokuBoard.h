#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include "SudokuCell.h"
#include "SudokuBoard.h"
#include "SudokuGenerator.h"
#include <set>
#include <vector>

class SudokuBoard
{
public:
    SudokuBoard();
    virtual ~SudokuBoard();
    void draw(SDL_Renderer *SDK_Renderer, bool draw_answer = false);
    void update(SDL_Event e);
    void setDifficulty(int difficulty);
    void destroy();
    bool hasWrong();
    void setLockingState(bool value);
    bool isWon();
    bool isLocked();
    bool hasSelectedCell();

private:
    int cellID(SDL_Point coordinate);
    SDL_Point reverseCellID(int encode);
    std::set<int> checkCell(int encodeID);
    SudokuGenerator generator;
    SudokuCell grid[9][9];
    const int EMPTY_CELL = -1;
    int selectedCell;
    bool hasWrongCell;
    // Graph for duplicated cell
    std::vector<std::set<int>> Graph;
    bool locked;
};

#endif // SUDOKUBOARD_H
