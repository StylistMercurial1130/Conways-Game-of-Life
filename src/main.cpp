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




/*
    int * gameworld = new int[(WINDOWHEIGHT/RESOLUTION) * (WINDOWWIDTH/RESOLUTION)];
    if(SDL_Init(SDL_INIT_VIDEO) != 0){

        SDL_Log("SDL Could not be initalized !");
        return EXIT_FAILURE;

    }

    Display display = Display(WINDOWHEIGHT,WINDOWWIDTH,"Test window");
    Controller controller = Controller();
    Game game = Game(WINDOWHEIGHT,WINDOWWIDTH,RESOLUTION);
    gameworld = game.Get_GameWorldBuffer();
    display.InitBufferSurface(gameworld,(WINDOWWIDTH/RESOLUTION),(WINDOWHEIGHT/RESOLUTION));

    while(controller.IsApplicationOpen()){

        controller.PollInput();
        gameworld[
                    controller.GetMouseXPosition() / RESOLUTION + 
                    ((controller.GetMouseYPosition() / RESOLUTION) * 64)
                ] = 0xffffffff;

        display.Draw(gameworld);
    }

    delete gameworld;
    SDL_Quit();

    return 0;

*/

