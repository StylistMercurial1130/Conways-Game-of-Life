#include "Application.h"

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

    Enter(){m_Newworld = nullptr;};

    virtual void StateRun() override;
    virtual void StateExit() override;
    virtual void StatePause() override;

};

class Pause : public State{

public : 

    virtual void StateRun() override;
    virtual void StateExit() override;
    virtual void StatePause() override;


};

class Exit : public State{

public : 
    
    virtual void StateRun() override;
    virtual void StateExit() override;
    virtual void StatePause() override;

};

class Run : public State{

public : 

    virtual void StateRun() override;
    virtual void StateExit() override;
    virtual void StatePause() override;

};

#pragma endregion ApplicationStates

#pragma region StateFunctions

void Enter ::StateRun(){

    if(m_Newworld != nullptr){

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

void Enter :: StateExit(){ delete m_Newworld;}

void Enter :: StatePause(){return;}

void Run :: StateRun(){

    this->m_Application->game.ClearGameBuffer();

    this->m_Application->game.UpdateGameWorld();

    this->m_Application->display.Draw(this->m_Application->game.Get_GameWorldBuffer());

}

void Run :: StatePause(){
    
}


#pragma endregion StateFunctions