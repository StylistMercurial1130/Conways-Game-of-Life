#pragma once
#include "SDL2/SDL.h"

class Display{

private : 

    SDL_Window * m_Displaywindow;
    SDL_Surface * m_Displaysurface;
    SDL_Surface * m_Buffersurface;
    SDL_Rect m_Displayrect;
    int m_Fps;
    int m_Framedelay;

public : 

    Display(int windowHeight,int windowWidth,const char * windowTitle,int fps);
    void InitBufferSurface(int * display,int windowWidth,int windowHeight);
    void Draw(int * display);
    int GetFrameDelay();
    int GetFrameRate();
    ~Display();

};