#include "SudokuBoard.h"
const int CELL_WIDTH = 80;
const int CELL_HEIGHT = 80;
const int THICKNESS = 4;
SudokuBoard::SudokuBoard()
{
    selectedCell = EMPTY_CELL;
    Graph.assign(81, std::set<int>());
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            SDL_Rect pos = {CELL_WIDTH * j, CELL_HEIGHT * i, CELL_WIDTH, CELL_HEIGHT};
            grid[i][j].setRect(pos);
        }
}
SudokuBoard::~SudokuBoard()
{
    destroy();
}
int SudokuBoard::cellID(SDL_Point coordinate)
{
    return coordinate.x * 9 + coordinate.y;
}

SDL_Point SudokuBoard::reverseCellID(int encode)
{
    return {encode / 9, encode % 9};
}

void SudokuBoard::setDifficulty(int difficulty)
{
    generator.generatePuzzle(difficulty);
    Graph.assign(81, std::set<int>());
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            grid[i][j].reset();
            grid[i][j].setLockedValue(generator.get(i, j));
            if (generator.get(i, j) != 0)
                grid[i][j].setLockingState(true);
            grid[i][j].setAnswerValue(generator.getAnswer(i, j));
        }
}

void SudokuBoard::draw(SDL_Renderer *SDK_Renderer, bool draw_answer)
{

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            grid[i][j].draw(SDK_Renderer, draw_answer);
    // draw thickness line
    SDL_Color bar_color = {0, 0, 0, 0};
    SDL_SetRenderDrawColor(SDK_Renderer, bar_color.r,
                           bar_color.g,
                           bar_color.b,
                           bar_color.a);
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect horizontal_line = {0, CELL_HEIGHT * 3 * i, CELL_WIDTH * 9, THICKNESS};
        SDL_RenderFillRect(SDK_Renderer, &horizontal_line);
    }
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect vertical_line = {CELL_WIDTH * 3 * i, 0, THICKNESS, CELL_HEIGHT * 9};
        SDL_RenderFillRect(SDK_Renderer, &vertical_line);
    }
}
bool SudokuBoard::isWon()
{
    bool win = true;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (grid[i][j].getValue() != grid[i][j].getAnswer())
            {
                win = false;
                break;
            }
    return win;
}
bool SudokuBoard::hasSelectedCell()
{
    return selectedCell != EMPTY_CELL;
}
std::set<int> SudokuBoard::checkCell(int encodeID)
{
    std::set<int> filter;
    SDL_Point coordinate = reverseCellID(encodeID);
    int row = coordinate.x;
    int col = coordinate.y;
    // check row
    for (int c = 0; c < 9; c++)
        if (col != c && grid[row][col].getValue() == grid[row][c].getValue())
        {
            filter.insert(cellID({row, c}));
        }
    // check column

    for (int r = 0; r < 9; r++)
        if (row != r && grid[row][col].getValue() == grid[r][col].getValue())
        {
            filter.insert(cellID({r, col}));
        }

    // Check in box 3x3

    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;
    for (int dirX = 0; dirX < 3; dirX++)
        for (int dirY = 0; dirY < 3; dirY++)
        {
            int r = boxStartRow + dirX;
            int c = boxStartCol + dirY;
            if (!(r == row && c == col) && grid[r][c].getValue() == grid[row][col].getValue())
            {
                filter.insert(cellID({r, c}));
            }
        }
    return filter;
}

void SudokuBoard::update(SDL_Event e)
{
    if (locked)
        return;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            grid[i][j].handleMouseState(e);
            if (grid[i][j].isSelected())
            {
                if (selectedCell != EMPTY_CELL && selectedCell != cellID({i, j}))
                {
                    SDL_Point coordinateU = reverseCellID(selectedCell);
                    grid[coordinateU.x][coordinateU.y].setSelected(false);
                }
                selectedCell = cellID({i, j});
            }
        }

    hasWrongCell = false;
    if (selectedCell != EMPTY_CELL)
    {
        if (e.type == SDL_KEYDOWN)
        {
            SDL_Point coordinateU = reverseCellID(selectedCell);
            for (std::set<int>::iterator it = Graph[selectedCell].begin(); it != Graph[selectedCell].end(); it++)
            {
                int v = *it;
                Graph[v].erase(selectedCell);
                SDL_Point coordinateV = reverseCellID(v);
                grid[coordinateV.x][coordinateV.y].increaseDuplicate(-1);
                grid[coordinateU.x][coordinateU.y].increaseDuplicate(-1);
            }
            Graph[selectedCell].clear();
            grid[coordinateU.x][coordinateU.y].setWrong(false);

            grid[coordinateU.x][coordinateU.y].handleKeyboardState(e);

            if (grid[coordinateU.x][coordinateU.y].getValue() != 0)
            {
                std::set<int> duplicated_list = checkCell(selectedCell);
                if (duplicated_list.empty() == false)
                {

                    for (std::set<int>::iterator it = duplicated_list.begin(); it != duplicated_list.end(); it++)
                    {
                        int v = *it;
                        Graph[v].insert(selectedCell);
                        SDL_Point coordinateV = reverseCellID(v);
                        grid[coordinateV.x][coordinateV.y].increaseDuplicate(1);
                        grid[coordinateU.x][coordinateU.y].increaseDuplicate(1);
                    }
                    Graph[selectedCell] = duplicated_list;
                    grid[coordinateU.x][coordinateU.y].setWrong(true);
                    hasWrongCell = true;
                }
                else
                {
                    grid[coordinateU.x][coordinateU.y].setWrong(false);
                }
            }
        }
    }
}
bool SudokuBoard::hasWrong()
{
    return hasWrongCell;
}

void SudokuBoard::setLockingState(bool value)
{
    locked = value;
}

bool SudokuBoard::isLocked()
{
    return locked;
}

void SudokuBoard::destroy()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            grid[i][j].destroy();
    if (!Graph.empty())
    {

        for (int i = 0; i < 81; i++)
            Graph[i].clear();
        Graph.clear();
    }
}
