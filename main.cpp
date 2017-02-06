#include "camera.h"
#include "map.h"
#include "player.h"
#include "SDL_image.h"
#include "SDL.h"
#include "stdio.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
int teamSize = 10;
double gravity = 0.6;
Camera camera;

int main(int argc, char *argv[]){
    bool quit = false;
    //TODO make entity array
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window * window = NULL;
    window = SDL_CreateWindow("Starving Prince", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    //SDL_Texture ** toRender;

    Map level1;
    level1.init(renderer);

    Player player[teamSize];

    for(int i = 0; i < teamSize; i++){
        player[i].init(renderer, 200+i*50, 200, -100, gravity, 4, 15);
    }

    player[0].host = true;

    camera.x = player[0].x;
    camera.y = player[0].y;

    int animation_tick = 0;

    while(!quit){
        animation_tick++;
        if(animation_tick == 4) animation_tick = 0;

        //zindex, append each texture to an array, render in order

        SDL_Delay(10);
        SDL_PollEvent(&event);

        switch(event.type){
            case SDL_QUIT:
                quit = true; break;
        }

        level1.update(camera.x, camera.y);

        for(int i = 0; i < teamSize; i++){
            player[i].update(event, camera.x, camera.y);

            if(level1.isColliding(player[i]))
                player[i].colliding = true;
            else
                player[i].colliding = false;

            if(animation_tick == 0) player[i].animation.update();
        }

        camera.x = player[0].x*-1+640;
        camera.y = (player[0].y+player[0].z)*-1+360;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        //render
        level1.render(renderer);

        for(int i = 0; i < teamSize; i++){
            player[i].render(renderer);
            renderer = player[i].render(renderer);

        }

        //render End

        SDL_RenderPresent(renderer);
    }

    //destroy all player textures
    for(int i = 0; i < teamSize; i++){
        player[i].end();
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
