#include "Application.h"

#pragma region Application

void Application :: Transition(State * state){

    if(m_State != nullptr)
        delete m_State;
    this->m_State = state;
    this->m_State->SetContext(this);

}

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

    this->m_State = state;
}


Application :: ~Application(){

    delete m_State;

}

int Application :: GetWorldCol(){return m_Worldcol;}
int Application :: GetWorldRow(){return m_Worldrow;}

void State :: SetContext(Application * application){ this->m_Application = application; }

#pragma endregion Application

#pragma region ApplicationStates

class Enter : public State{

private : 
    int * newWorld;

public : 

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

void Enter ::StateRun(){

    this->m_Application->game.ClearGameBuffer();

    int row = m_Application->GetWorldRow();
    int col = m_Application->GetWorldCol();

    int * newWorld = new int[row * col];

}