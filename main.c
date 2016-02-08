#include <SDL2/SDL.h>

int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* fenetre = 0;
    SDL_Renderer* map = 0;
    SDL_CreateWindowAndRenderer(480,640,0,&fenetre,&map);
    SDL_SetRenderDrawColor(map, 0, 0, 0, 255);
    SDL_RenderClear(map);
    SDL_RenderPresent(map);

    //Boucle qui tiens la fenêtre ouverte.
    SDL_Event event;
    int repeat = 0;
    while(!repeat){

        SDL_SetRenderDrawColor(map,255,165,0,255);
        SDL_RenderDrawLine(map,0,0,300,300);
        SDL_RenderPresent(map);
        SDL_PollEvent(&event);
        switch(event.type){
        case SDL_QUIT:
            repeat=1;
            break;
        }
    }


    SDL_DestroyWindow(fenetre);
    return 0;
}
