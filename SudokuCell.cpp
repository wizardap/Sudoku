#include "SudokuCell.h"


const std::string fontfilepath = "fonts/Bungee-Regular.ttf";
SudokuCell::SudokuCell()
{
    SDK_State[MOUSE_OUT]= {255,255,255,255};
    SDK_State[MOUSE_IN] = {97,211,238,0};
    SDK_State[MOUSE_DOWN]= {76, 165, 187,0};
    SDK_State[LOCKED] = {213, 224, 81,0};
    SDK_State[WRONG] = {247, 207, 214,0};

    SDK_ColorFont[WRONG] = {255, 106, 47,0};
    SDK_ColorFont[DEFAULT] = {0,0,0,0};
    selected=false;
    wrong = false;
    locked=false;
    decided=false;
    duplicated=false;
    value =cachedValue =0;
    gCurrentState = MOUSE_OUT;
}
int SudokuCell::getAnswer()
{
    return answer_value;
}

SudokuCell::~SudokuCell()
{
    destroy();
}
void SudokuCell::setSelected(bool select)
{
    selected = select;
    if (!select)
        cachedValue=value;
}
void SudokuCell::setDuplicate(bool right)
{
    duplicated=right;
}


void SudokuCell::setLockedValue(int new_value)
{
    value = new_value;
    cachedValue=new_value;
}
void SudokuCell::setAnswerValue(int new_value)
{
    answer_value=new_value;
}


void SudokuCell::update(SDL_Event e)
{
    if (isLocked()) return;
    if (isSelected())
    {
        handleKeyboardState(e);
    }
    else
    {
        handleMouseState(e);
    }
}
void SudokuCell::setWrong(bool right)
{
    wrong = right;
}


bool SudokuCell::isSame(SudokuCell cell)
{
    return (cell.gButtonRect.x == gButtonRect.x &&
            cell.gButtonRect.y == gButtonRect.y &&
            cell.gButtonRect.w == gButtonRect.w &&
            cell.gButtonRect.h == gButtonRect.h);
}

void SudokuCell::draw(SDL_Renderer* SDK_Renderer,bool draw_answer)
{
    // Draw the background of rect
    SDL_Color insideRect = SDK_State[(duplicated || wrong ? WRONG : gCurrentState)] ;
    SDL_SetRenderDrawColor(SDK_Renderer,insideRect.r,insideRect.g,insideRect.b,insideRect.a);
    SDL_RenderFillRect(SDK_Renderer,&gButtonRect);
    SDL_Color border = {0,0,0,0};
    SDL_SetRenderDrawColor(SDK_Renderer,border.r,border.g,border.b,border.a);
    SDL_RenderDrawRect(SDK_Renderer,&gButtonRect);

    // Draw value in the center of the rect
    DynamicText value_text(fontfilepath,20);
//    SDL_Log("%d",(wrong ? 1 : 0));
    SDL_Color value_color = (wrong ? SDK_ColorFont[WRONG] : SDK_ColorFont[DEFAULT]);
    int print_value = (draw_answer ? answer_value : cachedValue);
    value_text.loadText(SDK_Renderer,print_value==0 ? " " : std::to_string(print_value)
                        ,value_color);
    value_text.drawText(SDK_Renderer,
                        gButtonRect.x + (gButtonRect.w - value_text.getWidth())/2,
                        gButtonRect.y + (gButtonRect.h - value_text.getHeight())/2);

}
void SudokuCell::handleKeyboardState(SDL_Event e)
{
    if (isLocked()) return;
    if (e.type == SDL_KEYDOWN)
    {
        SDL_Log("Key Pressed!");
        switch (e.key.keysym.sym)
        {
        case SDLK_1:
            cachedValue =1;
            break;
        case SDLK_2:
            cachedValue = 2;
            break;
        case SDLK_3:
            cachedValue = 3;
            break;
        case SDLK_4:
            cachedValue =4;
            break;
        case SDLK_5:
            cachedValue =5;
            break;
        case SDLK_6:
            cachedValue = 6;
            break;
        case SDLK_7:
            cachedValue = 7;
            break;
        case SDLK_8:
            cachedValue = 8;
            break;
        case SDLK_9:
            cachedValue = 9;
            break;
        case SDLK_BACKSPACE:
            cachedValue = 0;
            break;
        case SDLK_RETURN:
            value = cachedValue;
            decided= true;
            setSelected(false);
            break;
        }
        SDL_Log("%d",cachedValue);
    }
}


void SudokuCell::locking()
{
    locked=true;
    gCurrentState=LOCKED;

}

bool SudokuCell::isInside(int x, int y)
{
    return (x>=gButtonRect.x &&
            x<=gButtonRect.x + gButtonRect.w &&
            y>=gButtonRect.y &&
            y<=gButtonRect.y + gButtonRect.h);
}

void SudokuCell::handleMouseState(SDL_Event e)
{
    if (isLocked()) return;
    if (isSelected())
    {
//        gCurrentState = MOUSE_DOWN;
        SDL_Log("Selected already!");
    }
    else if (e.type ==SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION)
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        if (isInside(x,y)==false)
            gCurrentState = MOUSE_OUT;
        else
        {
            gCurrentState = MOUSE_IN;
            SDL_Log("Processing.....");
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                gCurrentState = MOUSE_DOWN;
                setSelected(true);
                SDL_Log("Cell is selected!");
            }

        }
    }
}


bool SudokuCell::isCorrect()
{
    return value == answer_value;
}

bool SudokuCell::isLocked()
{
    return locked;
}

bool SudokuCell::isSelected()
{
    return selected;
}

void SudokuCell::setRect(SDL_Rect rect)
{
    gButtonRect = rect;
}

void SudokuCell::destroy()
{

    selected=false;
    wrong = false;
    locked=false;
    decided=false;
    duplicated=false;
    value =cachedValue =0;
}


int SudokuCell::getValue()
{
    return value;
}

