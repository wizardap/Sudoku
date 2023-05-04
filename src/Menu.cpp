#include "Menu.h"

Menu::Menu()
{
    gCurrentState = MAIN;
    gCurrentButtonType = TYPE_TOTAL;
    gButtonText[NEWGAME].setRect({700, 200, 0, 0});
    gButtonText[TUTORIAL].setRect({700, 250, 0, 0});
    gButtonText[RULE].setRect({700, 300, 0, 0});
    gButtonText[QUIT].setRect({700, 350, 0, 0});
}

Menu::~Menu()
{
    destroy();
}

bool Menu::init(SDL_Renderer *Menu_Renderer)
{
    if (gButtonText[NEWGAME].init(Menu_Renderer, "New Game") == false)
    {
        SDL_Log("Failed to load NEWGAME button in Menu.cpp");
        return false;
    }
    if (gButtonText[TUTORIAL].init(Menu_Renderer, "Tutorial") == false)
    {
        SDL_Log("Failed to load TUTORIAL button in Menu.cpp");
        return false;
    }
    if (gButtonText[RULE].init(Menu_Renderer, "Rule") == false)
    {
        SDL_Log("Failed to load Rule button in Menu.cpp");
        return false;
    }
    if (gButtonText[QUIT].init(Menu_Renderer, "Exit Game") == false)
    {
        SDL_Log("Failed to load QUIT button in Menu.cpp");
        return false;
    }
    if (gReturn.init(Menu_Renderer, "assets/Menu/Return") == false)
    {
        SDL_Log("Failed to load RETURN button in Menu.cpp");
        return false;
    }
    if (menu_background.loadImage(Menu_Renderer, "assets/Menu/menu.png") == false)
    {
        SDL_Log("Failed to load menu backround!");
        return false;
    }
    if (tutorial_background.loadImage(Menu_Renderer, "assets/Menu/tutorial.png") == false)
    {
        SDL_Log("Failed to load tutorial background!");
        return false;
    }
    if (rule_background.loadImage(Menu_Renderer, "assets/Menu/rule.png") == false)
    {
        SDL_Log("Failed to load tutorial background!");
        return false;
    }
    return true;
}

void Menu::run(SDL_Renderer *Menu_Renderer, SoundManager *SoundPlay)
{
    SDL_Event e;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            else
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                    SoundPlay->playChunk("click.wav");
                if (gCurrentState == MAIN)
                {
                    for (int i = 0; i < TYPE_TOTAL; i++)
                    {
                        gButtonText[i].update(e);
                    }
                    if (gButtonText[TUTORIAL].isSelected())
                    {
                        gCurrentButtonType = TUTORIAL;
                        gCurrentState = TUTORIAL_MAIN;
                    }
                    if (gButtonText[NEWGAME].isSelected())
                    {
                        gCurrentButtonType = NEWGAME;
                        running = false;
                    }
                    if (gButtonText[RULE].isSelected())
                    {
                        gCurrentButtonType = RULE;
                        gCurrentState = RULE_MAIN;
                    }
                    if (gButtonText[QUIT].isSelected())
                    {
                        gCurrentButtonType = QUIT;
                        running = false;
                    }
                }
                else
                {
                    gReturn.update(e);
                    if (gReturn.isSelected())
                    {
                        gCurrentState = MAIN;
                    }
                }
            }
        }
        draw(Menu_Renderer);
    }
}
void Menu::draw(SDL_Renderer *Menu_Renderer)
{
    SDL_SetRenderDrawColor(Menu_Renderer, 255, 255, 255, 0);
    SDL_RenderClear(Menu_Renderer);
    if (gCurrentState == TUTORIAL_MAIN)
    {
        tutorial_background.render(Menu_Renderer, 0, 0);
        gReturn.draw(Menu_Renderer);
    }
    if (gCurrentState == RULE_MAIN)
    {
        rule_background.render(Menu_Renderer, 0, 0);
        gReturn.draw(Menu_Renderer);
    }
    else if (gCurrentState == MAIN)
    {
        menu_background.render(Menu_Renderer, 0, 0);
        for (int i = 0; i < TYPE_TOTAL; i++)
            gButtonText[i].draw(Menu_Renderer);
    }

    SDL_RenderPresent(Menu_Renderer);
}

bool Menu::isNewGame()
{
    return gCurrentButtonType == NEWGAME;
}

bool Menu::isQuit()
{
    return gCurrentButtonType == QUIT;
}

bool Menu::isTutorial()
{
    return gCurrentButtonType == TUTORIAL;
}

void Menu::destroy()
{
    for (int i = 0; i < TYPE_TOTAL; i++)
        gButtonText[i].destroy();
    gReturn.destroy();
    menu_background.destroy();
    rule_background.destroy();
    tutorial_background.destroy();
}
