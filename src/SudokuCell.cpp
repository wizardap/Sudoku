#include "SudokuCell.h"

const std::string fontfilepath = "Bungee-Regular.ttf";
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
    duplicated=0;
    value_text = new DynamicText(FontManager->getFont(fontfilepath,20));
    value =cachedValue =0;
    gCurrentState = MOUSE_OUT;
}
void SudokuCell::reset()
{
    gCurrentState = MOUSE_OUT;
    selected=false;
    wrong = false;
    locked=false;
    duplicated=0;
    value =cachedValue =0;

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
}
void SudokuCell::increaseDuplicate(int amount)
{
    duplicated+=amount;
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
    SDL_Color insideRect = SDK_State[((duplicated>0 && !draw_answer)||wrong ? WRONG : gCurrentState)] ;
    SDL_SetRenderDrawColor(SDK_Renderer,insideRect.r,insideRect.g,insideRect.b,insideRect.a);
    SDL_RenderFillRect(SDK_Renderer,&gButtonRect);
    SDL_Color border = {0,0,0,0};
    SDL_SetRenderDrawColor(SDK_Renderer,border.r,border.g,border.b,border.a);
    SDL_RenderDrawRect(SDK_Renderer,&gButtonRect);

    // Draw value in the center of the rect

//    SDL_Log("%d",(wrong ? 1 : 0));
    SDL_Color value_color = (wrong ? SDK_ColorFont[WRONG] : SDK_ColorFont[DEFAULT]);
    int print_value = (draw_answer ? answer_value : cachedValue);
    value_text->loadText(SDK_Renderer,print_value==0 ? " " : std::to_string(print_value)
                         ,value_color);
    value_text->drawText(SDK_Renderer,
                         gButtonRect.x + (gButtonRect.w - value_text->getWidth())/2,
                         gButtonRect.y + (gButtonRect.h - value_text->getHeight())/2);

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
        }
        value = cachedValue;
    }
}


void SudokuCell::setLockingState(bool value)
{
    locked = value;
    if (locked) gCurrentState = LOCKED;
    else gCurrentState = MOUSE_OUT;
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
    else if (e.type ==SDL_MOUSEBUTTONDOWN  || e.type == SDL_MOUSEMOTION)
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
//        SDL_Log("%d %d",x,y);
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


bool SudokuCell::isWrong()
{
    return wrong;
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
    duplicated=0;
    value =cachedValue =0;
    value_text=NULL;
}


int SudokuCell::getValue()
{
    return value;
}



