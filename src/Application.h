
#pragma once

#include "Game.h"
#include "Display.h"

#define MAXSTATES 3

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
    bool m_Isrunning;
    void ApplicationRun();
    void ApplicationPause();
    void ApplicationExit();
    void (Application :: *FunctionPointers[MAXSTATES])();
     
public : 
    Display display;
    Game game;
    SDL_Event m_Event;
    Application(State * state, int Displayheight, int Displaywidth , int resolution , const char * windowTitle,int fps);
    void Transition(State * state);
    int GetWorldCol();
    int GetWorldRow();
    int GetMousePosX();
    int GetMousePosY();
    bool CheckMouseClick();
    void SetMousePos();
    int InputToStateFunction();
    void CallStateFunction(int functionPointerindex);
    State * GetState();
    bool GetIsRunning();
    void ToggleIsRunning();
    ~Application();

};

void _main();