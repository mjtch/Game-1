#ifndef animation_h
#define animation_h
#include "SDL_image.h"
#include "SDL.h"
#include "stdio.h"
#include "string"

class Animation
{
    public:

        int anchorX = -95;
        int anchorY = -190;
        int currentFrame = 0;
        int length;
        bool loop;
        bool paused;
        SDL_Texture ** frame;

        void init(bool _loop, bool _paused){
            loop = _loop;
            paused = _paused;
        }

        void loadAnimation(SDL_Renderer * renderer, std::string path, int selW, int selH, int col, int row, int _length){
            length = _length;
            frame = new SDL_Texture * [length];

            SDL_Surface * input = IMG_Load(path.c_str());

            SDL_Surface * output;
            //frame[0] = SDL_CreateTextureFromSurface(renderer, orig);

            SDL_Rect sel = {0, 0, selW, selH};
            SDL_Rect des = sel;

            for(int x = 0; x < col; x++){
                for(int y = 0; y < row; y++){
                    output = SDL_CreateRGBSurface(0, selW, selH, input->format->BitsPerPixel, input->format->Rmask, input->format->Gmask, input->format->Bmask, input->format->Amask);
                    int i = y*col+x;

                    if(i >= _length) break;

                    sel.x = x*selW;
                    sel.y = y*selH;

                    SDL_BlitSurface(input, &sel, output, &des);

                    frame[i] = SDL_CreateTextureFromSurface(renderer, output);

                    SDL_FreeSurface(output);
                }
            }
        }

        void update(){
            if(!paused){
                currentFrame++;

                if(currentFrame == length) currentFrame = 0;
            }
                /*if(loop){
                    if(currentFrame > length) currentFrame = 0;
                }else{
                    if(currentFrame == length) paused = true;
                }
            }*/
        }

        void pause(){
            paused = true;
        }

        void play(){
            paused = false;
        }

        void setFrame(int frameNumber){
            currentFrame = frameNumber;
        }

        SDL_Texture * showFrame(){
            return frame[currentFrame];
        }

        void destroy(){
            for(int i = 0; i < length; i++){
                SDL_DestroyTexture(frame[i]);
            }
        }
};


#endif
