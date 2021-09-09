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

    this->m_State = state;

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
bool Application :: CheckMouseClick(){return m_Onmouseclick;} 
int Application :: GetWorldCol(){return m_Worldcol;}
int Application :: GetWorldRow(){return m_Worldrow;}



void Application :: SetMousePos(int x , int y){

    if(m_Onmouseclick == true){

        m_Mousex = x / m_resolution;
        m_Mousey = y / m_resolution;

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

    /*
        Set Game World for the first time here !
    */

    


    this->m_Application->game.SetGameWorld( m_Newworld,
                                            m_Application->GetWorldRow(),
                                            this->m_Application->GetWorldCol());


}

void Enter :: StateExit(){ delete m_Newworld;}

#pragma endregion StateFunctions