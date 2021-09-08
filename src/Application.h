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


};

class Application{

private : 

    State * m_State;

public : 
    Display display;
    Game game;
    Application(State * state);
    void Transition(State * state);
    ~Application();

};