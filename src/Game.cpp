#include "Game.h"

Game::Game()
{
    started = false;
    paused = false;

    give_up = false;
}

Game::~Game()
{
    close();
}

bool Game::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("SDL could not be intialized! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    Game_Window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);

    if (Game_Window == NULL)
    {
        SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    Game_Renderer = SDL_CreateRenderer(Game_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (Game_Renderer == NULL)
    {
        SDL_Log("Renderer could not be created! SDL Error :%s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(Game_Renderer, 255, 255, 255, 255);
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        SDL_Log("Image could not be initialized! IMG Error :%s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    /// Initialize additional libriary

    if (SoundPlayer->addChunk("click.wav") == false)
    {
        SDL_Log("Failed to load click.wav !");
        return false;
    }
    if (SoundPlayer->addChunk("niceturn.wav") == false)
    {
        SDL_Log("Failed to load niceturn.wav !");
        return false;
    }
    if (SoundPlayer->addChunk("wrong.wav") == false)
    {
        SDL_Log("Failed to load wrong.wav !");
        return false;
    }

    if (SoundPlayer->addMusic("losing.mp3") == false)
    {
        SDL_Log("Failed to load losing.mp3 !");
        return false;
    }

    if (SoundPlayer->addMusic("winning.mp3") == false)
    {
        SDL_Log("Failed to load winning.mp3 !");
        return false;
    }
    if (SoundPlayer->addMusic("Chill.mp3") == false)
    {
        SDL_Log("Failed to load Faded.mp3 !");
        return false;
    }

    WindowLogo = IMG_Load("assets/WindowLogo/SDK.png");
    if (WindowLogo == NULL)
    {
        SDL_Log("Failed to load Window Logo Icon ! IMG Error :%s", IMG_GetError());
        return false;
    }

    if (Game_Notice.init(Game_Renderer) == false)
    {
        SDL_Log("Failed to initialize Notice!");
        return false;
    }
    if (Game_Timer.init(Game_Renderer) == false)
    {
        SDL_Log("Failed to initialize timer !");
        return false;
    }
    if (Game_Turn.init(Game_Renderer) == false)
    {
        SDL_Log("Failed to load turn of game !");
        return false;
    }
    if (Game_Option.init(Game_Renderer) == false)
    {
        SDL_Log("Failed to initialize Option!");
        return false;
    }

    if (Game_Menu.init(Game_Renderer) == false)
    {
        SDL_Log("Failed to initialize Menu!");
        return false;
    }
    return true;
}
void Game::render()
{
    SDL_SetRenderDrawColor(Game_Renderer, 242, 223, 208, 255);
    SDL_RenderClear(Game_Renderer);
    Game_Board.draw(Game_Renderer, give_up);
    Game_Timer.draw(Game_Renderer);
    Game_Notice.draw(Game_Renderer);
    Game_Turn.draw(Game_Renderer);
    Game_Option.draw(Game_Renderer);
    SDL_RenderPresent(Game_Renderer);
}

void Game::run()
{
    if (!init())
    {
        SDL_Log("Failed to initialize");
        return;
    }

    SDL_SetWindowIcon(Game_Window, WindowLogo);
    SoundPlayer->playMusic("Chill.mp3");
    Game_Menu.run(Game_Renderer, SoundPlayer);
    if (Game_Menu.isNewGame())
    {
        bool running = true;
        SDL_Event e;
        paused = false;
        started = true;
        Game_Timer.start();
        Game_Notice.waiting();
        Game_Option.resetState();
        Game_Board.setLockingState(false);
        Game_Board.setDifficulty(1);
        Game_Turn.setDefaultFoul(allow_fouls);
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
                    Game_Option.update(e);
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        SoundPlayer->playChunk("click.wav");
                    }
                    switch (Game_Option.CurrentState)
                    {
                    case Options::NEWGAME:
                        surrender(false);
                        Game_Turn.setDefaultFoul(allow_fouls);
                        start();
                        break;
                    case Options::SURRENDER:
                        if (started)
                        {
                            Game_Notice.gameover();
                            surrender(true);
                            SoundPlayer->stopMusic();
                            SoundPlayer->playMusic("losing.mp3");
                            pause();
                        }
                        break;
                    case Options::SOUND_OFF:
                        SoundPlayer->setMute(true);
                        break;
                    case Options::SOUND_ON:
                        SoundPlayer->setMute(false);
                        break;
                    case Options::EXIT:
                        running = false;
                        break;
                    default:
                        if (started)
                        {
                            Game_Board.update(e);
                            if (!Game_Board.isLocked())
                            {

                                if (Game_Board.hasWrong())
                                {

                                    Game_Turn.increaseFoul(1);
                                    Game_Notice.wrong();
                                    if (Game_Turn.lose())
                                    {
                                        Game_Timer.pause();
                                        Game_Board.setLockingState(true);
                                        Game_Notice.gameover();
                                        SoundPlayer->stopMusic();
                                        SoundPlayer->playMusic("losing.mp3");
                                    }
                                    else
                                    {
                                        SoundPlayer->playChunk("wrong.wav");
                                    }
                                }
                                else
                                {
                                    if (Game_Board.isWon())
                                    {
                                        Game_Timer.pause();
                                        Game_Board.setLockingState(true);
                                        Game_Notice.winning();
                                        SoundPlayer->stopMusic();
                                        SoundPlayer->playMusic("winning.mp3");
                                    }
                                    else if (e.type == SDL_KEYDOWN && Game_Board.hasSelectedCell())
                                    {
                                        if (e.key.keysym.sym >= SDLK_1 && e.key.keysym.sym <= SDLK_9)
                                        {
                                            Game_Notice.niceturn();
                                            SoundPlayer->playChunk("niceturn.wav");
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
            render();
        }
    }
    close();
}
void Game::start()
{
    paused = false;
    started = true;
    SoundPlayer->stopMusic();
    SoundPlayer->playMusic("Chill.mp3");
    Game_Timer.start();
    Game_Notice.waiting();
    Game_Option.resetState();
    Game_Board.setLockingState(false);
    Game_Board.setDifficulty(1);
}

void Game::pause()
{
    if (started && !paused)
    {

        paused = true;
        started = false;
        Game_Timer.pause();
        Game_Board.setLockingState(true);
    }
}

void Game::surrender(bool value)
{
    give_up = value;
}

void Game::close()
{
    Game_Timer.destroy();
    Game_Turn.destroy();
    Game_Board.destroy();
    Game_Option.destroy();

    FontManager->destroy();
    SDL_DestroyRenderer(Game_Renderer);
    Game_Renderer = NULL;

    SDL_DestroyWindow(Game_Window);
    Game_Window = NULL;
}
