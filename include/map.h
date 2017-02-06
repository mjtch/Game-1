#include "iostream"
#include "fstream"
#include "string"
#include "player.h"

class Map {
    public:
        SDL_Texture * ground;
        SDL_Texture * stairs;
        int mapWidth = 20;
        int mapHeight = 10;
        int mapDepth = 1;
        int tileWidth = 50;
        int tileHeight = 50;
        int tileDepth = 100;
        int level[10][20] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
        SDL_Rect dest;
        int renderX;
        int renderY;

        void init(SDL_Renderer * renderer){
            ground = SDL_CreateTextureFromSurface(renderer, IMG_Load("res/tiles/wooden_floor.png"));
            stairs = SDL_CreateTextureFromSurface(renderer, IMG_Load("res/tiles/wooden_slope_right.png"));
        }

        void update(int cameraX, int cameraY){
            renderX = cameraX;
            renderY = cameraY;
        }

        SDL_Renderer * render(SDL_Renderer * renderer){
            dest = {0, 0, 55, 65};

            for(int y = 0; y < mapHeight; y++){

                for(int x = 0; x < mapWidth; x++){
                    dest.x = x*tileWidth+renderX;
                    dest.y = y*tileHeight+renderY;

                    if(level[y][x] == 1){
                        dest.h = 65;
                        SDL_RenderCopy(renderer, ground, NULL, &dest);
                    }
                    /*if(level[y][x] == 2){
                        dest.h = 205;
                        dest.y -= 100;
                        SDL_RenderCopy(renderer, stairs, NULL, &dest);
                    }*/
                }
            }

            return renderer;
        }

        bool isColliding(Player player){
            for(int y = 0; y < mapHeight; y++){
                for(int x = 0; x < mapWidth; x++){
                    if(player.x > x*tileWidth && player.x <= x*tileWidth+tileWidth && player.y > y*tileHeight && player.y <= y*tileHeight+tileHeight && player.z > 0){
                        if(level[y][x] == 1) return true;
                    }
                }
            }

            return false;
        }
};
