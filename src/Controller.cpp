#include "Controller.h"
#include <iostream>

Controller :: Controller(){states = m_States :: APPLICATION_OPEN;}
int Controller :: GetMouseXPosition() {return m_Xmousepos;}
int Controller :: GetMouseYPosition() {return m_Ymousepos;}

bool Controller :: IsApplicationOpen(){ 

    if(states == m_States :: APPLICATION_CLOSE)
        return false;
    else if(states == m_States :: APPLICATION_OPEN)
                return true;

}

void Controller :: PollInput(){

    if(SDL_PollEvent(&m_Event)){

        switch(m_Event.type){

            case SDL_MOUSEBUTTONDOWN : {

                m_Xmousepos = m_Event.button.x;
                m_Ymousepos = m_Event.button.y; 

            } break;

            case SDL_QUIT : {

                states = m_States :: APPLICATION_CLOSE;
                
            }
        }

    }

}

void Controller :: PrintMousePosition(){
    
    std::cout<<m_Xmousepos<<"\t"<<m_Ymousepos<<std::endl;

}
