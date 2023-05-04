#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H
#include "Texture.h"
#include "DynamicText.h"
#include "SDK_ults.h"
class SudokuCell
{
public:
    SudokuCell();
    virtual ~SudokuCell();
    void update(SDL_Event e);
    void draw(SDL_Renderer* SDK_Renderer,bool draw_answer =  false);
    void destroy();
    void handleKeyboardState(SDL_Event e);
    void handleMouseState(SDL_Event e);
    int getValue();
    int getAnswer();
    bool isWrong();
    bool isLocked();
    bool isSelected();

    void setRect(SDL_Rect rect);
    void setLockingState(bool value);
    bool isSame(SudokuCell cell);
    void setLockedValue(int new_value);
    void setAnswerValue(int new_value);
    bool isInside(int x,int y);
    void setSelected(bool select = false);
    void increaseDuplicate(int amount);
    void setWrong(bool right = false);
    void reset();
protected:
    bool selected;

private:
    enum State
    {
        WRONG,
        DEFAULT,
        MOUSE_IN,
        MOUSE_OUT,
        MOUSE_DOWN,
        LOCKED,
        STATE_TOTAL
    };
    bool locked;
    bool wrong;
    SDL_Color SDK_State[STATE_TOTAL];
    SDL_Color SDK_ColorFont[2];
    State gCurrentState;
    int value,cachedValue,answer_value;
    int duplicated;
    SDL_Rect gButtonRect;
    DynamicText *value_text;
};



#endif // SUDOKUCELL_H
