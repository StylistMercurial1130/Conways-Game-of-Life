#include "Input.h"

void Input :: PollInput(){

    if(SDL_PollEvent(&m_Event)){

        switch(m_Event.type){

            case SDL_MOUSEBUTTONDOWN : {

                m_Xmousepos = m_Event.button.x;
                m_Ymousepos = m_Event.button.y; 

            } break;

        }

    }

}