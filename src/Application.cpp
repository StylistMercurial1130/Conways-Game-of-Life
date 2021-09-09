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

void Enter ::StateRun(){

    if(m_Newworld != nullptr){

        int row = this->m_Application->GetWorldRow();
        int col = this->m_Application->GetWorldCol();

        m_Newworld = new int[row * col];

        /*
            Set Game World for the first time here !
        */

        this->m_Application->game.SetGameWorld(m_Newworld,row,col);

        delete m_Newworld;

    }

}