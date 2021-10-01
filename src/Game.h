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
    int * GetGameInterface();
    int GetResolution();
    void SetGameWorld();
    void SetGameInterface(int x , int y);
    void SetGameInterface();
    ~Game();

};