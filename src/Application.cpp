#include "Application.h"

#pragma region Application

void Application :: Transition(State * state){

    if(m_State != nullptr)
        delete m_State;
    this->m_State = state;
    this->m_State->SetContext(this);

}

Application :: Application(State * state) : m_State(nullptr) , display(480,640,"title") , game(480,640,10){

    this->m_State = state;
}


Application :: ~Application(){

    delete m_State;

}

void State :: SetContext(Application * application){ this->m_Application = application; }

#pragma endregion Application

#pragma region ApplicationStates

class Enter : public State{

};

class Pause : public State{};

class Exit : public State{};

class Run : public State{};


#pragma endregion ApplicationStates

