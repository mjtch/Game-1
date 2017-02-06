#include "SDL.h"

class HUD {
    public:
        SDL_Texture * healthContainer;

        void init(SDL_Renderer * renderer){
            healthContainer = SDL_CreateTextureFromSurface(renderer, "res/HUD/health_bar.png");
        }

        SDL_Renderer * render(SDL_Renderer * renderer){


            return renderer;
        }
};
