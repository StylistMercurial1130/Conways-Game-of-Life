#pragma once
#include "SDL2/SDL.h"

class Display{

private : 

    SDL_Window * m_Displaywindow;
    SDL_Surface * m_Displaysurface;
    SDL_Surface * m_Buffersurface;
    SDL_Rect m_Displayrect;

public : 

    Display(int windowHeight,int windowWidth,const char * windowTitle);
    ~Display();

};