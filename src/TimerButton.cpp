#include "TimerButton.h"
const std::string fontfilepath = "Bungee-Regular.ttf";
TimerButton::TimerButton()
{
    gButtonRect = {790,0,240,113};
}

TimerButton::~TimerButton()
{
    destroy();
}
bool TimerButton::init(SDL_Renderer* Time_Renderer)
{
    mText = new DynamicText(FontManager->getFont(fontfilepath,26));
    if (mTexture.loadImage(Time_Renderer,"assets/Timer/timer.png")==false)
    {
        SDL_Log("Could not load timer rectangle!");
        return false;
    }

    return true;
}


void TimerButton::draw(SDL_Renderer* Time_Renderer)
{

    mTexture.setStretching(gButtonRect.w,gButtonRect.h);
    mTexture.render(Time_Renderer,gButtonRect.x,gButtonRect.y);

    SDL_Color timer_color = {0,0,0,0};


    if ( mText->loadText(Time_Renderer,time_format(),timer_color)==false)
    {
        SDL_Log("Could not load timer!");

    }
    mText->drawText(Time_Renderer,
                        gButtonRect.x + (gButtonRect.w - mText->getWidth())/2,
                        gButtonRect.y + (gButtonRect.h - mText->getHeight())/2);
}

void TimerButton::start()
{
    mTimer.start();
}

void TimerButton::stop()
{
    mTimer.stop();
}

void TimerButton::pause()
{
    mTimer.pause();
}

void TimerButton::unpause()
{
    mTimer.unpause();
}


void TimerButton::destroy()
{
    mText->destroy();
    mTexture.destroy();
}
std::string TimerButton::time_format()
{
    std::string seconds = std::to_string((mTimer.getTicks()/1000)%60);
    std::string minutes = std::to_string((mTimer.getTicks()/60000)%60);
    std::string hours = std::to_string(mTimer.getTicks()/3600000);
    if ((int)hours.size()==1) hours="0"+hours;
    if ((int)minutes.size() == 1) minutes="0"+minutes;
    if ((int)seconds.size()== 1) seconds="0"+seconds;
    return hours +" : "+minutes+" : "+seconds;
}





