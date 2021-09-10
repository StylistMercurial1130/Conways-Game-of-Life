/**
 * @file Application.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#pragma once

#include "Game.h"
#include "Display.h"

class Application;

class State{

protected : 

    Application * m_Application;

public : 

    virtual ~State() {
        delete m_Application;
    }

    void SetContext(Application * application);

    virtual void pause() = 0;
    virtual void run() = 0;
    virtual void exit() = 0;
    virtual void state() = 0;

};

class Application{

private : 

    State * m_State;
    int m_Worldcol , m_Worldrow;
    int m_Displayheight , m_Displaywidth;
    int m_resolution;
    int m_Mousex, m_Mousey;
    bool m_Onmouseclick;
    SDL_Event m_Event;

public : 
    Display display;
    Game game;
    Application(State * state, int Displayheight, int Displaywidth , int resolution , const char * windowTitle);
    void Transition(State * state);
    int GetWorldCol();
    int GetWorldRow();
    int GetMousePosX();
    int GetMousePosY();
    bool CheckMouseClick();
    void SetMousePos();
    void Run();
    void Exit();
    void Pause();
    ~Application();

};