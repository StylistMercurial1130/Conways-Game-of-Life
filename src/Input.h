#pragma one

#include "SDL2/SDL.h"

class Input{

private : 

    SDL_Event m_Event;
    int m_Xmousepos, m_Ymousepos;

public :

    void PollInput();

};