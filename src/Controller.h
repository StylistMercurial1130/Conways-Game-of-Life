#pragma one

#include "SDL2/SDL.h"

class Controller{

private : 

    SDL_Event m_Event;
    int m_Xmousepos, m_Ymousepos;
    enum class m_States {APPLICATION_OPEN , APPLICATION_CLOSE , APPLICATION_PAUSE};
    m_States states;

public :

    Controller();
    bool IsApplicationOpen();
    void PollInput();
    void PrintMousePosition();
    int GetMouseXPosition();
    int GetMouseYPosition();
};
