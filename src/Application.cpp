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

    display.InitBufferSurface(game.Get_GameWorld(),m_Worldcol,m_Worldrow);

    Transition(state);

}

void Application :: Transition(State * state){

    if(m_State != nullptr)
        delete m_State;
    this->m_State = state;
    this->m_State->SetContext(this);

}


Application :: ~Application(){

    delete m_State;

}

int Application :: GetMousePosX(){return m_Mousex;}
int Application :: GetMousePosY(){return m_Mousey;}
int Application :: GetWorldCol(){return m_Worldcol;}
int Application :: GetWorldRow(){return m_Worldrow;}

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

void State :: SetContext(Application * application){ this->m_Application = application; }

#pragma endregion Application

#pragma region ApplicationStates



class Enter : public State{

private : 

    int * m_Newworld;

public : 

    Enter(){m_Newworld = nullptr;}

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

    delete this->m_Newworld;
    this->m_Application->Transition(new Exit);

}

void Enter :: state(){

    
    if(m_Newworld == nullptr){

        int row = this->m_Application->GetWorldRow();
        int col = this->m_Application->GetWorldCol();

        m_Newworld = new int[row * col];

        for(int i = 0; i < row * col;i++)
            m_Newworld[i] = 0;
    }

    if(this->m_Application->CheckMouseClick()){

        this->m_Application->SetMousePos();

        int x = this->m_Application->GetMousePosX();
        int y = this->m_Application->GetMousePosY();

        m_Newworld[x + (y * this->m_Application->GetWorldCol())] = 0xfffffff;

        this->m_Application->game.SetGameWorld( m_Newworld,
                                                m_Application->GetWorldRow(),
                                                this->m_Application->GetWorldCol());

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

    this->m_Application->game.ClearGameBuffer();
    this->m_Application->game.UpdateGameWorld();
    

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

        this->m_Application->game.SetGameWorld(x,y);

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

        application.display.Draw(application.game.Get_GameWorld());

    }

}

#pragma endregion _Main