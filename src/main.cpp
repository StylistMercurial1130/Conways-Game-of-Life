#include "Application.h"
#include "SDL2/SDL.h"
#include <iostream>

using namespace std;

#define WINDOWHEIGHT 480
#define WINDOWWIDTH 640
#define RESOLUTION 10

int main(int argc, char *argv[]){


    if(SDL_Init(SDL_INIT_VIDEO) != 0){

        SDL_Log("SDL could not be initalized ! \n");
        SDL_Log(SDL_GetError());

        return EXIT_FAILURE;

    }


    _main();

    return 0;

}





