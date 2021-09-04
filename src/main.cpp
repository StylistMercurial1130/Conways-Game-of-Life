#include <iostream>
#include "Display.h"
#include "Controller.h"
#include "Game.h"
#include "SDL2/SDL.h"

using namespace std;

#define WINDOWHEIGHT 480
#define WINDOWWIDTH 640
#define RESOLUTION 10

int main(int argc, char *argv[]){

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


}