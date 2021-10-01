#include "Application.h"

#define WINDOWHEIGHT 480
#define WINDOWWIDTH 640
#define RESOLUTION 10


#pragma region Application

Application :: Application( State * state, 
                            int Displayheight, int Displaywidth , 
                            int resolution , 
                            const char * windowTitle) : 
m_State(nullptr) , 
display(Displayheight,Displaywidth,windowTitle) , 
game(Displayheight,Displaywidth,resolution){

    m_Worldrow = Displayheight / resolution;
    m_Worldcol = Displaywidth / resolution;
    m_resolution = resolution;

    display.InitBufferSurface(game.GetGameInterface(),m_Worldcol,m_Worldrow);

    FunctionPointers[0] = &ApplicationRun;
    FunctionPointers[1] = &ApplicationPause;
    FunctionPointers[2] = &ApplicationExit;

    Transition(state);

}

void Application :: Transition(State * state){

    if(m_State != nullptr)
        m_State = nullptr;
    this->m_State = state;
    this->m_State->SetContext(this);

}

bool Application :: CheckMouseClick(){

    if(m_Event.type == SDL_MOUSEBUTTONDOWN)
        m_Onmouseclick = true;
    else 
        m_Onmouseclick = false;

    return m_Onmouseclick;
} 

void Application :: SetMousePos(){

    if(m_Onmouseclick == true){

        SDL_GetMouseState(&m_Mousex,&m_Mousey);

        m_Mousex = m_Mousex / m_resolution;
        m_Mousey = m_Mousey / m_resolution;

        m_Onmouseclick = false;

    }

}

int Application :: InputToStateFunction(){

    switch(m_Event.type){

        case SDL_KEYDOWN : 
                switch(m_Event.key.keysym.sym){

                    case SDLK_r : return 0;
                    break;

                    case SDLK_p : return 1;
                    break;

                }
        break;

    }

    return - 1;

}

void Application :: CallStateFunction(int functionPointerindex){

    (this->*FunctionPointers[functionPointerindex])();
}

Application :: ~Application(){delete m_State;}
void Application :: ApplicationRun(){this->m_State->run();}
void Application :: ApplicationPause(){this->m_State->pause();}
void Application :: ApplicationExit(){this->m_State->exit();}
State * Application :: GetState(){return m_State;}
int Application :: GetMousePosX(){return m_Mousex;}
int Application :: GetMousePosY(){return m_Mousey;}
int Application :: GetWorldCol(){return m_Worldcol;}
int Application :: GetWorldRow(){return m_Worldrow;}
void State :: SetContext(Application * application){ this->m_Application = application; }


#pragma endregion Application

#pragma region ApplicationStates

class Enter : public State{

public : 


    virtual void pause() override;
    virtual void run() override;
    virtual void exit() override;
    virtual void state() override;

};


class Exit : public State{

public : 

    virtual void pause() override;
    virtual void run() override;
    virtual void exit() override;
    virtual void state() override;

};


class Run : public State{

public : 

    virtual void pause() override;
    virtual void run() override;
    virtual void exit() override;
    virtual void state() override;

};


class Pause : public State{

public : 

    virtual void pause() override;
    virtual void run() override;
    virtual void exit() override;
    virtual void state() override;

};


void Enter :: pause(){return;}

void Enter :: run(){

    this->m_Application->Transition(new Run);
}

void Enter :: exit(){

    this->m_Application->Transition(new Exit);

}

void Enter :: state(){
    
    if(this->m_Application->CheckMouseClick()){

        this->m_Application->SetMousePos();

        int x = this->m_Application->GetMousePosX();
        int y = this->m_Application->GetMousePosY();


        this->m_Application->game.SetGameInterface(x,y);

    }

}

void Run :: pause(){
    
    this->m_Application->Transition(new Pause);

}

void Run :: run(){return;}

void Run :: exit(){

    this->m_Application->Transition(new Exit);

}

void Run :: state(){

    this->m_Application->game.SetGameWorld();
    this->m_Application->game.ClearGameBuffer();
    this->m_Application->game.UpdateGameWorld();
    this->m_Application->game.SetGameInterface();

}

void Pause :: pause(){return;}

void Pause :: run(){
    this->m_Application->Transition(new Run);
}

void Pause :: exit(){

    this->m_Application->Transition(new Exit);

}

void Pause :: state(){
    
    if(this->m_Application->CheckMouseClick()){

        this->m_Application->SetMousePos();
        int x = this->m_Application->GetMousePosX();
        int y = this->m_Application->GetMousePosY();

        this->m_Application->game.SetGameInterface(x,y);
    }

}

void Exit :: pause(){return;}
 
void Exit :: run(){return;}

void Exit :: exit(){return;}

void Exit :: state(){return;}

#pragma endregion ApplicationStates

#pragma region _Main



void _main(){

    Application application =  Application( new Enter,
                                            WINDOWHEIGHT,WINDOWWIDTH,
                                            RESOLUTION,
                                            "Conways Game of Life");

    while(1){

        SDL_PollEvent(&application.m_Event);
        if(application.InputToStateFunction() != -1){
            application.CallStateFunction(application.InputToStateFunction());
        }
        application.GetState()->state();
        application.display.Draw(application.game.GetGameInterface());

    }

}

#pragma endregion _Main


