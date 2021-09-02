#include "Controller.h"
#include <iostream>


void Controller :: PollInput(){

    if(SDL_PollEvent(&m_Event)){

        switch(m_Event.type){

            case SDL_MOUSEBUTTONDOWN : {

                m_Xmousepos = m_Event.button.x;
                m_Ymousepos = m_Event.button.y; 

            } break;

            case SDL_QUIT : {

                SDL_Quit();
                
            }
        }

    }

}

void Controller :: PrintMousePosition(){
    
    std::cout<<m_Xmousepos<<"\t"<<m_Ymousepos<<std::endl;

}
