/**
 * @file main.cpp
 * @author StylistMercurial(V.Karthik)
 * @brief 
 * Entery point of the Application 
 * @version 0.1
 * @date 2021-10-02
 * 
 */

//indcludes and macros
#include "Application.h"
#include "SDL2/SDL.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]){

    //Initializing SDL.
    if(SDL_Init(SDL_INIT_VIDEO) != 0){

        SDL_Log("SDL could not be initalized ! \n");
        SDL_Log(SDL_GetError());

        return EXIT_FAILURE;

    }

    /**
     * @brief Entery point for the Application 
     * after initializing SDL.
     */
    _main();

    //Calling SDL_Quit() at the end of the application.
    atexit(SDL_Quit);

    return 0;

}





