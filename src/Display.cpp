#include "Display.h"

Display :: Display(int displayWidth,int displayHeight, int resolution){

    m_Displaywidth = displayWidth;
    m_DisplayHeight = m_DisplayHeight;
    m_Resolution = resolution;

    int rows = m_Displaywidth / m_Resolution;
    int columns = m_DisplayHeight / m_Resolution;

    m_Display = new uint32_t[rows * columns];
    m_Buffer = new uint32_t[rows * columns];

}

Display :: ~Display(){

    delete m_Buffer;
    delete m_Display;

}