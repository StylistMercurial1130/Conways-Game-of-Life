#include "Display.h"

Display :: Display(int windowHeight,int windowWidth,const char * windowTitle){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){

        SDL_Log("SDL could not be initialized !");
        SDL_Log(SDL_GetError());

        return;

    }

    m_Displaywindow = SDL_CreateWindow( windowTitle,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        windowWidth,windowHeight,
                                        SDL_WINDOW_SHOWN);

    if(m_Displaywindow == NULL){
        
        SDL_Log("Could not create window !");
        SDL_Log(SDL_GetError());

        return;

    }

    m_Displaysurface = SDL_GetWindowSurface(m_Displaywindow);

    if(m_Displaysurface == NULL){
        
        SDL_Log("Could not create window Surface !");
        SDL_Log(SDL_GetError());

        return;

    }

    m_Displayrect.x = m_Displayrect.y = 0;
    m_Displayrect. h = windowHeight;
    m_Displayrect.w = windowWidth;

}

Display :: ~Display(){

    SDL_FreeSurface(m_Buffersurface);
    SDL_FreeSurface(m_Displaysurface);
    SDL_DestroyWindow(m_Displaywindow);
    
}