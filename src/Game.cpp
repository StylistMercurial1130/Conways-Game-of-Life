#include "Game.h"
#include <iostream>

#define FILTER(X) (X == 0xffffffff ? 1 : 0)
#define _FILTER(X) (X == 1 ? 0xffffffff : 0x00000000)

int * Game :: GetGameInterface(){return m_Interface;} 
int Game :: GetResolution(){return m_Resolution;}

Game :: Game(int height,int width,int resolution){

    m_Gameheigth = height;
    m_Gamewidth = width;
    m_Resolution = resolution;

    int row = m_Gamewidth / m_Resolution;
    int col = m_Gameheigth / m_Resolution;

    m_Gameworld = new int[row * col]; 
    m_Gameworldbuffer = new int[row * col];
    m_Interface = new int[row * col];

    for(int i = 0; i < row;i++)
        for(int j = 0;j < col;j++){

            m_Gameworld[j + i * col] = 0;
            m_Gameworldbuffer[j + i * col] = 0;
            m_Interface[j + i * col] = 0x00000000;

        }
             

}

void Game :: UpdateGameWorld(){

    int row = m_Gameheigth / m_Resolution;
    int col = m_Gamewidth / m_Resolution;

    for(int i = 0;i < row;i++){
        for(int j = 0;j < col;j++){
            
            int state = CalculateCellState(j,i);

            if(m_Gameworld[j + i * col] == 0){

                if(state == 3) 
                    m_Gameworldbuffer[j + i * col] = 1;

            } else if(m_Gameworld[j + i * col] == 1) {

                        if(state < 2 || state > 3)
                            m_Gameworldbuffer[j + i * col] = 0;
                        else 
                            m_Gameworldbuffer[j + i * col] = 1;
            
                    }
           
        }

    }

    
    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++){
            m_Gameworld[j + i * col] = m_Gameworldbuffer[j + i * col];
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
    for(int i = -1;i < 2;i++){

        for(int j = - 1;j < 2;j++){

            int x_pos = (j + x_worldPosition);
            int y_pos = (i + y_worldPosition);


            if((x_pos >= 0 && x_pos <= col - 1) && (y_pos >= 0 && y_pos <= row - 1) ){
                sum += m_Gameworld[x_pos + col * y_pos];
            }
        }

    }
        
    sum -= m_Gameworld[x_worldPosition + y_worldPosition * col];

    return sum;

}

void Game :: SetGameWorld(){
    
    int row = m_Gameheigth / m_Resolution;
    int col = m_Gamewidth / m_Resolution;

    for(int i = 0; i < row * col;i++)
        m_Gameworld[i] = FILTER(m_Interface[i]);

}

void Game :: SetGameInterface(int x , int y){

    int row = m_Gameheigth / m_Resolution;
    int col = m_Gamewidth / m_Resolution;

    if(x <= (col - 1) && y <= (row - 1))
        m_Interface[x + col * y] = 0xffffffff;

}

void Game :: SetGameInterface(){

    int row = m_Gameheigth / m_Resolution;
    int col = m_Gamewidth / m_Resolution;

    for(int i = 0;i < row * col;i++)
        m_Interface[i] = _FILTER(m_Gameworld[i]);
    
}

Game :: ~Game(){

    delete m_Gameworld;
    delete m_Gameworldbuffer;
    delete m_Interface;

}