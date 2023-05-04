#ifndef SDK_ULTS_H
#define SDK_ULTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
class Font
{
public:
    Font();
    ~Font();
    TTF_Font *getFont(std::string filename, int ptsize);
    void destroy();

private:
    std::map<std::string, TTF_Font *> font_list;
};
static Font *FontManager = new Font;

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();
    void playChunk(std::string ID);
    bool addChunk(std::string filename);
    void setVolumeChunk(std::string ID, int volume);
    void setMute(bool value);
    void playMusic(std::string ID);
    void pauseMusic();
    void unpauseMusic();
    void stopMusic();
    bool addMusic(std::string filename);
    void setVolumeMusic(int volume);
    bool isMuted();
    void destroy();

private:
    std::map<std::string, Mix_Chunk *> chunk_list;
    std::map<std::string, Mix_Music *> music_list;
    const int DEFAULT_CHUNK_VOLUME = 20;
    const int DEFAULT_MUSIC_VOLUME = 100;
    bool muted;
};

static SoundManager *SoundPlayer = new SoundManager;

#endif // SDK_ULTS_H
