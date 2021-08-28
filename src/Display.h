#pragma once
#include <inttypes.h>


class Display{

private : 

    int m_Displaywidth , m_DisplayHeight;
    int m_Resolution;
    uint32_t * m_Display;
    uint32_t * m_Buffer;
  
public : 

    Display(int displayWidth,int displayHeight, int resolution);

};