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
    m_Displayrect.h = windowHeight;
    m_Displayrect.w = windowWidth;

}

void Display :: InitBufferSurface(int * display,int windowWidth,int windowHeight){

    m_Buffersurface = SDL_CreateRGBSurfaceFrom( display,
                                                windowWidth,windowHeight,
                                                32,
                                                windowWidth * sizeof(int),
                                                0xff000000,0x00ff0000,0x0000ff00,0);


    SDL_SetSurfaceRLE(m_Buffersurface,1);
    
}

void Display :: Draw(int * display){

    SDL_LockSurface(m_Buffersurface);

    SDL_memcpy(m_Buffersurface->pixels,display,m_Buffersurface->h * m_Buffersurface->pitch);

    SDL_UnlockSurface(m_Buffersurface);

    SDL_BlitScaled(m_Buffersurface,NULL,m_Displaysurface,&m_Displayrect);
    SDL_UpdateWindowSurface(m_Displaywindow);

}

Display :: ~Display(){

    SDL_FreeSurface(m_Buffersurface);
    SDL_FreeSurface(m_Displaysurface);
    SDL_DestroyWindow(m_Displaywindow);
    
}