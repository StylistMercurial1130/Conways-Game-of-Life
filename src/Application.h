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

    void SetContext(Application * application);
    virtual void StateRun() = 0;
    virtual void StateExit() = 0;
    virtual void StatePause() = 0;

};

class Application{

private : 

    State * m_State;
    int m_Worldcol , m_Worldrow;
    int m_Displayheight , m_Displaywidth;
    int m_resolution;


public : 
    Display display;
    Game game;
    Application(State * state, int Displayheight, int Displaywidth , int resolution , const char * windowTitle);
    void Transition(State * state);
    int GetWorldCol();
    int GetWorldRow();
    void Run();
    void Exit();
    void Pause();
    ~Application();

};