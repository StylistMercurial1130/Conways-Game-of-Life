#pragma once

class Game{

private : 

    int * m_Gameworld;
    int * m_Gameworldbuffer;
    int * m_Interface;
    int m_Gamewidth,m_Gameheigth;
    int m_Resolution;

    int CalculateCellState(int x_worldPosition,int y_worldPosition);

public : 

    Game(int height,int width,int resolution);
    void ClearGameBuffer();
    void UpdateGameWorld();
    int * GetGameWorldBuffer();
    int * GetGameWorld();
    int Get_Resolution();
    void SetGameWorld(int * gameWorldinput,int inputRowsize,int inputColsize); 
    void SetGameWorld(int x, int y);
    ~Game();

};