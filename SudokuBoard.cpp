#include "SudokuBoard.h"
const int CELL_WIDTH = 80;
const int CELL_HEIGHT = 80;
const int THICKNESS  = 4;
SudokuBoard::SudokuBoard():
    selectedCell(NULL)
{
    for (int i = 0 ; i<9; i++)
        for (int j =0 ; j<9; j++)
        {
            SDL_Rect pos = {CELL_WIDTH*i,CELL_HEIGHT*j,CELL_WIDTH,CELL_HEIGHT};
            grid[i][j].setRect(pos);
        }


}
void SudokuBoard::setDifficulty(int difficulty)
{
    generator.generatePuzzle(difficulty);
    for (int i =0; i<9; i++)
        for (int j =0; j<9; j++)
        {
            grid[i][j].setLockedValue(generator.get(i,j));
            if (generator.get(i,j)!=0) grid[i][j].locking();
            grid[i][j].setAnswerValue(generator.getAnswer(i,j));
        }
}

SudokuBoard::~SudokuBoard()
{
    for (int i = 0 ; i<9; i++)
        for (int j =0 ; j<9; j++)
            grid[i][j].destroy();
    selectedCell=NULL;
}
void SudokuBoard::draw(SDL_Renderer* SDK_Renderer,bool draw_answer)
{
    for (int i = 0 ; i<9; i++)
        for (int j =0 ; j<9; j++)
            grid[i][j].draw(SDK_Renderer,draw_answer);
    // draw thickness line
    SDL_Color bar_color= {0,0,0,0};
    SDL_SetRenderDrawColor(SDK_Renderer,bar_color.r,
                           bar_color.g,
                           bar_color.b,
                           bar_color.a);
    for (int i =0; i<4; i++)
    {
        SDL_Rect horizontal_line= {0,CELL_HEIGHT*3*i,CELL_WIDTH*9,THICKNESS};
        SDL_RenderFillRect(SDK_Renderer,&horizontal_line);
    }
    for (int i =0; i<4; i++)
    {
        SDL_Rect vertical_line= {CELL_WIDTH*3*i,0,THICKNESS,CELL_HEIGHT*9};
        SDL_RenderFillRect(SDK_Renderer,&vertical_line);
    }

}
SudokuCell* SudokuBoard::checkRow(SudokuCell *cell, int row)
{
    SudokuCell *answer=NULL;
    for (int col = 0; col<9; col++)
        if (!cell->isSame(grid[row][col]) && grid[row][col].getValue() == cell->getValue())
        {
            answer = &grid[row][col];
        }
    return answer;

}
SudokuCell* SudokuBoard::checkInBox(SudokuCell *cell, int row, int col)
{
    SudokuCell *answer = NULL;
    int boxStartRow = row - row%3;
    int boxStartCol = col - col%3;
    for (int r = 0; r<3; r++)
        for (int c = 0; c<3; c++)
        {
            int x = boxStartRow +r;
            int y = boxStartCol + c;
            if (!cell->isSame(grid[x][y]) && grid[x][y].getValue() == cell->getValue())
            {
                answer = &grid[row][col];
            }
        }
    return answer;
}

SudokuCell* SudokuBoard::checkCol(SudokuCell *cell, int col)
{
    SudokuCell *answer=NULL;
    for (int row= 0; row<9; row++)
        if (!cell->isSame(grid[row][col]) && grid[row][col].getValue() == cell->getValue())
        {
            answer = &grid[row][col];
        }
    return answer;
}


void SudokuBoard::update(SDL_Event e)
{
    int x=-1,y=-1;
    for (int i =0; i<9; i++)
        for (int j =0; j<9; j++)
        {
            grid[i][j].handleMouseState(e);
            if (grid[i][j].isSelected())
            {
                if (selectedCell!=NULL && selectedCell!= &grid[i][j])
                {
                    selectedCell->setSelected(false);
                }

                selectedCell=&grid[i][j];
                x=i;
                y=j;
            }
        }

    if (selectedCell!=NULL)
    {
        selectedCell->handleKeyboardState(e);
        if (selectedCell->decided==true)
        {

            SudokuCell* sameRowCell = checkRow(selectedCell,x);
            SudokuCell* sameColCell = checkCol(selectedCell,y);
            SudokuCell* sameBox = checkInBox(selectedCell,x,y);
            std::vector<SudokuCell*> wrong_list;
            if (sameRowCell!=NULL)
                wrong_list.push_back(sameRowCell);
            if (sameColCell!=NULL)
                wrong_list.push_back(sameColCell);
            if (sameBox!=NULL)
                wrong_list.push_back(sameBox);
            if (wrong_list.empty() || selectedCell->getValue()==0)
            {
                if (wrong_cell.count(selectedCell)>0)
                {
                    std::vector<SudokuCell*> rollback_state= wrong_cell[selectedCell];
                    for (int i =0 ; i<int(rollback_state.size()); i++)
                    {
                        rollback_state[i]->setDuplicate(false);
                    }
                    wrong_cell.erase(selectedCell);
                }
                selectedCell->setWrong(false);
            }
            else
            {
                selectedCell->setWrong(true);
                wrong_cell.insert({selectedCell,wrong_list});
                for (int i =0; i<int(wrong_list.size()); i++)
                {
                    wrong_list[i]->setDuplicate(true);
                }
            }
            selectedCell->decided=false;
        }

    }


}
