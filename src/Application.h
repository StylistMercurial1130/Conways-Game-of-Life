/**
 * @file Application.h
 * @author StylistMercurial(V.Karthik)
 * @brief The Application header files
 *        
 *        This header file holds the applicaiton and state class
 * @version 0.1
 * @date 2021-10-02
 * 
 */
#pragma once

#include "Game.h"
#include "Display.h"

/**
 * @brief Max Number of States
 */
#define MAXSTATES 3

/**
 * @brief Application class prototype
 */
class Application;

/**
 * @brief The State class, a templete class for any type of Application state
 */
class State{

protected : 

    /**
     * @brief Application context
     */
    Application * m_Application;

public : 

    /**
     * @brief State class Destructor
     */
    virtual ~State() {
        delete m_Application;
    }

    void SetContext(Application * application);

    /**
     * @brief pause state function
     */
    virtual void pause() = 0;

    /**
     * @brief run state function
     */
    virtual void run() = 0;

    /**
     * @brief exit state function
     */
    virtual void exit() = 0;

    /**
     * @brief state action function
     */
    virtual void state() = 0;

};

/**
 * @brief The Applicaiton class
 */
class Application{

private : 

    /**
     * @brief holds the current state 
     */
    State * m_State;

    /**
     * @brief holds the game world dimenstion
     *          
     *          m_Worldcol : no of columns of the game world
     *          m_Worldrow : no of ros of the game world
     */
    int m_Worldcol , m_Worldrow;

    /**
     * @brief The display dimenstion
     * 
     *          m_Displayheight : the height of the display
     *          m_Displaywidth : the width of the display
     */
    int m_Displayheight , m_Displaywidth;

    /**
     * @brief The resolution by which the display dimenstion are scalled to 
     *        to give the world dimenstions
     */
    int m_resolution;

    /**
     * @brief The mouse x and y cordinates 
     *      
     *          m_Mousex : x position of the mouse
     *          m_Mousey : y position of the mouse
     */
    int m_Mousex, m_Mousey;

    /**
     * @brief Keeps track where the mouse was clicked
     */
    bool m_Onmouseclick;

    /**
     * @brief Keeps in check wether the applicaion is running or not
     */

    bool m_Isrunning;

    void ApplicationRun();

    void ApplicationPause();

    void ApplicationExit();

    /**
     * @brief The funciton pointer array that holds the state functions
     */
    void (Application :: *FunctionPointers[MAXSTATES])();
     
public : 

    /**
     * @brief The Display class object
     */
    Display display;

    /**
     * @brief The Game class object
     */
    Game game;

    /**
     * @brief SLD_Event
     */
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