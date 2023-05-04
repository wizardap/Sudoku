#include "SDK_ults.h"

Font::Font()
{

}

Font::~Font()
{
    destroy();
}

TTF_Font* Font::getFont(std::string filename, int ptsize)
{
    std::string fullPath;
    fullPath+="fonts/";
    fullPath+=filename;
    std::string key = fullPath+std::to_string(ptsize);

    if (font_list.count(key) == 0)
    {
        if (TTF_Init()==-1)
        {
            SDL_Log("Doesn't init!");
        }
        font_list[key] = TTF_OpenFont(fullPath.c_str(),ptsize);
        if (font_list[key] == NULL)
        {
            SDL_Log("Failed to load font %s ! TTF Error : %s",filename.c_str(),TTF_GetError());
        }
    }
    return font_list[key];
}

void Font::destroy()
{
    for (std::map<std::string,TTF_Font*>::iterator it = font_list.begin(); it!=font_list.end(); it++)
        if (it->second !=NULL)
            TTF_CloseFont(it->second);
    font_list.clear();
}


SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
    destroy();

}
void SoundManager::setMute(bool value)
{
    muted = value;
    setVolumeMusic((value ? 0 : DEFAULT_MUSIC_VOLUME));
    for (std::map<std::string,Mix_Chunk*>::iterator it = chunk_list.begin(); it!=chunk_list.end(); it++)
        setVolumeChunk(it->first,(value ? 0 : DEFAULT_CHUNK_VOLUME));
}

void SoundManager::playChunk(std::string ID)
{
    if (chunk_list.count(ID)==0)
    {
        SDL_Log("Unavailable chunk which name is %s !",ID.c_str());
        return;
    }
    Mix_PlayChannel(-1,chunk_list[ID],0);
}

bool SoundManager::addChunk(std::string filename)
{
    std::string fullpath = "sound/Chunk/"+filename;
    if (chunk_list.count(filename)==0)
    {
        chunk_list[filename] = Mix_LoadWAV(fullpath.c_str());
        if (chunk_list[filename] == NULL)
        {
            SDL_Log("Failed to load %s chunk! Mix Error: %s",fullpath.c_str(),Mix_GetError());
            return false;
        }
    }
    setVolumeChunk(filename,DEFAULT_CHUNK_VOLUME);
    return true;
}

void SoundManager::setVolumeChunk(std::string ID,int volume)
{
    if (chunk_list.count(ID)==0)
    {
        SDL_Log("Unavailable chunk which name is %s !",ID.c_str());
        return;
    }

    Mix_VolumeChunk(chunk_list[ID],volume*128/100);
}

void SoundManager::playMusic(std::string ID)
{
    if (music_list.count(ID) == 0)
    {
        SDL_Log("Unavailable music which name is %s !",ID.c_str());
        return;
    }
    if (Mix_PlayingMusic()==0)
    {
        Mix_PlayMusic(music_list[ID],-1);
    }
}

void SoundManager::pauseMusic()
{
    if (Mix_PausedMusic()!=1)
    {
        Mix_PauseMusic();
    }
}

void SoundManager::unpauseMusic()
{
    if (Mix_PausedMusic()==1)
    {
        Mix_ResumeMusic();
    }
}

void SoundManager::stopMusic()
{
    if (Mix_PlayingMusic()!=0)
    {
        Mix_HaltMusic();
    }
}


bool SoundManager::addMusic(std::string filename)
{
    std::string fullpath = "sound/Music/" + filename;
    if (music_list.count(filename)==0)
    {
        music_list[filename] = Mix_LoadMUS(fullpath.c_str());
        if (music_list[filename] == NULL)
        {
            SDL_Log("Failed to load %s music! Mix Error: %s",fullpath.c_str(),Mix_GetError());
            return false;
        }
    }
    setVolumeMusic(DEFAULT_MUSIC_VOLUME);
    return true;
}

void SoundManager::setVolumeMusic(int volume)
{
    //Volume range from 0 to 100 ( normal)
    Mix_VolumeMusic(volume);
}

void SoundManager::destroy()
{
    for (std::map<std::string,Mix_Chunk*>::iterator it = chunk_list.begin(); it!=chunk_list.end(); it++)
        if (it->second!=NULL)
            Mix_FreeChunk(it->second);
    for (std::map<std::string,Mix_Music*>::iterator it = music_list.begin(); it!=music_list.end(); it++)
        if (it->second!=NULL)
            Mix_FreeMusic(it->second);
}
bool SoundManager::isMuted()
{
    return muted;
}
