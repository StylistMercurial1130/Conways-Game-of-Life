#include "Game.h"

Game :: Game(int height,int width,int resolution){

    m_Gameheigth = height;
    m_Gamewidth = width;
    m_Resolution = resolution;

    int row = m_Gamewidth / m_Resolution;
    int col = m_Gameheigth / m_Resolution;

    m_Gameworld = new int[row * col]; 
    m_Gameworldbuffer = new int[row * col];

    for(int i = 0; i < row;i++)
        for(int j = 0;j < col;j++)
            m_Gameworld[j + i * col] = m_Gameworldbuffer[j + i * col] = 0;

}

int * Game :: Get_GameWorldBuffer(){ return m_Gameworldbuffer;}

void Game :: UpdateGameWorld(){

    int row = m_Gameheigth / m_Resolution;
    int col = m_Gamewidth / m_Resolution;

    for(int i = 0;i < row;i++){
        for(int j = 0;j < col;j++){

            int state = CalculateCellState(j,i);
            
            if(m_Gameworld[j + i * col] == 0)
                if(state == 3)
                    m_Gameworldbuffer[j + i * col] = 1;
            else if(m_Gameworld[j + i * col] == 1){
                    if(state < 2 || state > 3)
                        m_Gameworldbuffer[j + i * col] = 0;
                    else
                        m_Gameworldbuffer[j + i * col] = 1;

                }

        }

    }

}

void Game :: ClearGameBuffer(){
    
    int row = m_Gameheigth / m_Resolution;
    int col = m_Gamewidth / m_Resolution;

    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++)
            m_Gameworldbuffer[j + i * col] = 0;

}

int Game ::  CalculateCellState(int x_worldPosition,int y_worldPosition){

    
    int row = m_Gameheigth / m_Resolution;
    int col = m_Gamewidth / m_Resolution;

    int sum = 0;
    for(int i = -1;i < 2;i++)
        for(int j = - 1;j < 2;j++){

            int x_Pos = (j + x_worldPosition + col) % col;
            int y_pos = (i + y_worldPosition + row) % row;

            sum += m_Gameworld[x_Pos + y_pos * col];

        }
    
    sum -= m_Gameworld[x_worldPosition + y_worldPosition * col];

    return sum;

}



Game :: ~Game(){

    delete m_Gameworld;
    delete m_Gameworldbuffer;

}