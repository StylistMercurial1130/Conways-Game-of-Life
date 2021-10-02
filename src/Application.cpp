/**
 * @file Application.cpp
 * @author StylistMercurial(V.Karthik)
 * @brief 
 * The Application, Ties all the components together.
 * 
 * The Application uses state machine pattern. The Application has 4 states
 * 
 * 1.Pause
 * 2.Run
 * 3.Exit
 * 4.Enter
 * 
 * The Application starts by default in the Enter state, where the gameworld is set
 * using a interface array to which the update game world is transfered to after 
 * each update call. 
 * The Run state runs the application.
 * The Pause state pauses the application. 
 * The Exit state exits the application.
 * @version 0.1
 * @date 2021-10-02
 */

#include "Application.h"

/**
 * @brief 
 * macros :
 *  
 *  WINDOWHEIGHT : Height of the Application Window 
 *  WINDOWWIDTH : Width of the Application Window
 *  MAXFPS : Max Frames Per Second of the Application
 *  RESOLUTION : The Factor by which the Window Dimensions are devided to 
 *               give the Game World Dimnesion.
 */
#define WINDOWHEIGHT 480
#define WINDOWWIDTH 640
#define MAXFPS 15
#define RESOLUTION 10

//Application Region
#pragma region Application

/**
 * @brief Application Class Constructor
 * 
 * @param state The State the Applicaiton should enter 
 * @param Displayheight The height of the application window display
 * @param Displaywidth  the width of the application window display
 * @param resolution  the resolution by which the appliction window is devided by to 
 *                    give the world dimensions 
 * @param windowTitle the title of the application
 * @param fps the maximum frames per second of the application
 */
Application :: Application( State * state, 
                            int Displayheight, int Displaywidth , 
                            int resolution , 
                            const char * windowTitle,
                            int fps) : 
m_State(nullptr) , 
display(Displayheight,Displaywidth,windowTitle,fps) , 
game(Displayheight,Displaywidth,resolution){

    /**
     * Setting the world Parameters
     * m_Worldrow is the no of rows of the world array
     * m_Worldcol is the no of cols of the world col
     * m_resolution is the resolution the display array uses to make the game world
     */
    m_Worldrow = Displayheight / resolution;
    m_Worldcol = Displaywidth / resolution;
    m_resolution = resolution;

    /**
     * Initializing the buffer surface
     * This is set the dimensions of the world
     */
    display.InitBufferSurface(game.GetGameInterface(),m_Worldcol,m_Worldrow);

    /**
     * Setting the Function Pointer array elements
     * Each element corresponds to a state function
     */
    FunctionPointers[0] = &ApplicationRun;
    FunctionPointers[1] = &ApplicationPause;
    FunctionPointers[2] = &ApplicationExit;

    /**
     * Transitions to the default state / state given while calling the constructor
     */
    Transition(state);

    /**
     * setting the applciation running bool to true
     * Keeping track whether the application is running or not 
     * via the m_Isrunning, at the call of the constructor its toggled on
     */
    m_Isrunning = true;
}

/**
 * @brief Transitions / sets the m_State to the state passed to the function
 * 
 * @param state the state the application shall transition to
 */
void Application :: Transition(State * state){
    
    /**
     * checking whether the m_state is a null to make sure multiple m_state.
     */
    if(m_State != nullptr)
        m_State = nullptr;
    /**
     * Setting the m_State to the state passed to the function and 
     * setting the context/application object pointer to the current object 
     * of application.
     */
    this->m_State = state;
    this->m_State->SetContext(this);

}

/**
 * @brief Checks for mouse click, if true it set m_Onmouseclick to true otherwise
 *        false 
 */
bool Application :: CheckMouseClick(){

    /**
     * checking for the mouseclicks
     */
    if(m_Event.type == SDL_MOUSEBUTTONDOWN)
        m_Onmouseclick = true;
    else 
        m_Onmouseclick = false;

    //returning the m_ONmouseclick for debugging purposes
    return m_Onmouseclick;
} 

/**
 * @brief to set the mouse x and y codinate on click
 */
void Application :: SetMousePos(){

    /**
     * checking if the mouse was clicked
     */
    if(m_Onmouseclick == true){

        /**
         * Getting the mouse cordinates when clicked
         */
        SDL_GetMouseState(&m_Mousex,&m_Mousey);

        /**
         * Setting the mouse x and y cordinates with respect to the game world
         * by scalling the cordinates by the m_resolution
         */
        m_Mousex = m_Mousex / m_resolution;
        m_Mousey = m_Mousey / m_resolution;

        /**
         * Resetting the m_Onmouseclick to register future clicks
         */
        m_Onmouseclick = false;

    }

}

/**
 * @brief Associating Eaching input as a value between 0 and 2. This acts like a 
 *        hashing function that takes a input and returns a index for the Functionpointer 
 *        array which is a array of function pointers
 * 
 *          r key is associated with index 0
 *          p key is associated with 1 
 *          q key is associated iwth 2 
 *          SDL_QUIT Event types is associated with 2
 */
int Application :: InputToStateFunction(){

    /**
     * Checking if the event type is of SDL_KEYDOWN or SDL_QUIT
     */
    switch(m_Event.type){

        /**
         * Key pressed Event
         */
        case SDL_KEYDOWN : 
                /**
                 * Returning the index based on key pressed
                 */
                switch(m_Event.key.keysym.sym){

                    case SDLK_r : return 0;
                    break;

                    case SDLK_p : return 1;
                    break;

                    case SDLK_q : return 2;
                    break;

                }
        break;
        
        /**
         * SDL Quit Event
         */
        case SDL_QUIT : return 2;
        break;

    }

    return - 1;

}

/**
 * @brief Calls the state function from of the FunctionPointer array
 *        based on the index passed to the function
 * 
 * @param functionPointerindex the index of the function to be called from the function
 *                             pointer
 */
void Application :: CallStateFunction(int functionPointerindex){(this->*FunctionPointers[functionPointerindex])();}
/**
 * @brief Applicaion class deconstructor 
 *  
 */
Application :: ~Application(){delete m_State;}
/**
 * @brief There are 3 state functions 
 *          
 *          1.ApplicaitonRun()
 *          2.ApplicationPause()
 *          3.ApplicationExit()
 * 
 * Each function could be considered a state action, which either invokes 
 * a transition to another state or a action associated with state function
 */

/**
 * @brief The Run State function
 */
void Application :: ApplicationRun(){this->m_State->run();}

/**
 * @brief the Pause state function
 */
void Application :: ApplicationPause(){this->m_State->pause();}

/**
 * @brief the Exit state function
 */
void Application :: ApplicationExit(){this->m_State->exit();}

/**
 * @brief Returns the current state of the application
 */
State * Application :: GetState(){return m_State;}

/**
 * @brief Returns the mouse x position stored
 */
int Application :: GetMousePosX(){return m_Mousex;}

/**
 * @brief Returns the mouse y position stored
 */
int Application :: GetMousePosY(){return m_Mousey;}

/**
 * @brief Returns the no of colums that exist in the game world
 */
int Application :: GetWorldCol(){return m_Worldcol;}

/**
 * @brief Returns the no of rows that exist in the game world
 */
int Application :: GetWorldRow(){return m_Worldrow;}

/**
 * @brief Sets the application pointer/ context of the current state
 * 
 * @param application the application object which is set as the context of the 
 *                    current state
 */
void State :: SetContext(Application * application){ this->m_Application = application; }

/**
 * @brief Returns the m_Isrunning variable which tracks wheter the application is 
 *        running or not 
 */
bool Application :: GetIsRunning(){return m_Isrunning;}

/**
 * @brief Toggles m_Isrunning when called
 */
void Application :: ToggleIsRunning(){m_Isrunning = (!m_Isrunning);}


#pragma endregion Application

//Application States
#pragma region ApplicationStates

/**
 * @brief Each State is class which inherits from the base class 
 *        State class whose functions are overriden by each of the state 
 *        class
 *        
 *          A State has 4 functions that are associated to its functioning
 *          
 *          1.pause() : Pause action
 *          2.run() : Run action
 *          3.exit() : Exit action
 *          4.State() : the action that runs the function of that state
 */

/**
 * @brief The Enter state
 */
class Enter : public State{

public : 


    virtual void pause() override;
    virtual void run() override;
    virtual void exit() override;
    virtual void state() override;

};

/**
 * @brief The Exit state
 */
class Exit : public State{

public : 

    virtual void pause() override;
    virtual void run() override;
    virtual void exit() override;
    virtual void state() override;

};


/**
 * @brief The Run state
 */
class Run : public State{

public : 

    virtual void pause() override;
    virtual void run() override;
    virtual void exit() override;
    virtual void state() override;

};

/**
 * @brief The Pause state
 */
class Pause : public State{

public : 

    virtual void pause() override;
    virtual void run() override;
    virtual void exit() override;
    virtual void state() override;

};

/**
 * @brief Each of the state functions and their defintions
 */

/**
 * @brief the pause action of the Enter state
 */
void Enter :: pause(){return;}

/**
 * @brief the run action fo the Enter class
 */
void Enter :: run(){

    this->m_Application->Transition(new Run);
}

/**
 * @brief the exit action of the Enter state
 */
void Enter :: exit(){

    this->m_Application->Transition(new Exit);

}

/**
 * @brief The state action associated to the Enter state.
 *          
 *          This function sets the game world when the appplication 
 *          just starts.
 */
void Enter :: state(){
    
    if(this->m_Application->CheckMouseClick()){

        this->m_Application->SetMousePos();

        int x = this->m_Application->GetMousePosX();
        int y = this->m_Application->GetMousePosY();


        this->m_Application->game.SetGameInterface(x,y);

    }

}

/**
 * @brief The pause action of the Run state
 */
void Run :: pause(){
    
    this->m_Application->Transition(new Pause);

}

/**
 * @brief the run action of the Run state 
 */
void Run :: run(){return;}

/**
 * @brief the ext action fothe Run state
 */
void Run :: exit(){

    this->m_Application->Transition(new Exit);

}

/**
 * @brief The state function associated with Run state
 *          
 *          This functions updated the game world every call and 
 *          sets the game interface which is displayed.
 */
void Run :: state(){

    this->m_Application->game.SetGameWorld();
    this->m_Application->game.ClearGameBuffer();
    this->m_Application->game.UpdateGameWorld();
    this->m_Application->game.SetGameInterface();

}

/**
 * @brief The pause function associated with Pause state
 */
void Pause :: pause(){return;}

/**
 * @brief The run function associated with Pause state
 */
void Pause :: run(){
    this->m_Application->Transition(new Run);
}

/**
 * @brief The exit function associated with Pause state
 */
void Pause :: exit(){

    this->m_Application->Transition(new Exit);

}

/**
 * @brief The state function associated with Pause state
 *          
 *          This function allows to set the game world when in the pause 
 *          state
 */
void Pause :: state(){
    
    if(this->m_Application->CheckMouseClick()){

        this->m_Application->SetMousePos();
        int x = this->m_Application->GetMousePosX();
        int y = this->m_Application->GetMousePosY();

        this->m_Application->game.SetGameInterface(x,y);
    }

}

/**
 * @brief The pause function associated with Exit state 
 */
void Exit :: pause(){this->m_Application->ToggleIsRunning();}
 
/**
 * @brief the run funciton associated with Run state
 */
void Exit :: run(){this->m_Application->ToggleIsRunning();}

/**
 * @brief the exit function associated with Exit state
 */
void Exit :: exit(){this->m_Application->ToggleIsRunning();}

/**
 * @brief the state function associated with Exit state
 *          
 *          This toggles the m_Isrunnign, making to false
 *          which signals the closing of the application
 */
void Exit :: state(){this->m_Application->ToggleIsRunning();}

#pragma endregion ApplicationStates


//Application Main entery
#pragma region _Main

/**
 * @brief The Entry point of the Application
 */
void _main(){

    /**
     * Creating a object of application
     */
    Application application =  Application( new Enter,
                                            WINDOWHEIGHT,WINDOWWIDTH,
                                            RESOLUTION,
                                            "Conways Game of Life",
                                            MAXFPS);

    /**
     * Variables the record the time take for frame to finish and start of the frame
     */
    uint32_t framestart,frametime;

    /**
     * Application loop
     */
    while(application.GetIsRunning()){

        /**
         * Polling for Events and Inputs
         */
        SDL_PollEvent(&application.m_Event);
        if(application.InputToStateFunction() != -1){
            /**
             * Calling a state function based on input recieved
             */
            application.CallStateFunction(application.InputToStateFunction());
        }
        
        /**
         * Capturing the time of the start of frame
         */
        framestart = SDL_GetTicks();

        /**
         * Executing the state function of the current sate
         */
        application.GetState()->state();

        /**
         * Calling the draw function to draw the game interface
         */
        application.display.Draw(application.game.GetGameInterface());

        /**
         * Capturing the end of the frame
         */
        frametime = SDL_GetTicks() - framestart;

        /**
         * Delaying the next fram by the time difference between each frame time 
         * and set frame delay corresponding to set frame rate.
         */
        if(application.display.GetFrameDelay() > frametime)
            SDL_Delay(application.display.GetFrameDelay() - frametime);

    }

}

#pragma endregion _Main


