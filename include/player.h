#ifndef player_h
#define player_h

#include "SDL_image.h"
#include "SDL.h"
#include "stdio.h"
#include "keys.h"
#include "animation.h"

class Player
{
    public:
        int championID;
        bool host = false;
        bool colliding = false;
        Keys keyboard;
        double x, y, z;
        double renderX, renderY;
        double gravity, vel;
        double speed, jumpHeight;
        SDL_Texture * sprite;
        Animation animation;

        SDL_Rect playerSize;

        void init(SDL_Renderer * renderer, double _x, double _y, double _z, double _gravity, double _speed, double _jumpHeight){
            animation.init(true, false);
            animation.loadAnimation(renderer, "res/Kevin/run.png", 920, 920, 4, 4, 13);

            sprite = animation.frame[0];

            x = _x;
            y = _y;
            z = _z;
            gravity = _gravity;
            speed = _speed;
            jumpHeight = _jumpHeight;

            playerSize.w = 200;
            playerSize.h = 200;

            //run.loadAnimation(_renderer, "res/Kevin/run.png", 980, 920, 4, 4, 4);
        }

        void update(SDL_Event event, int cameraX, int cameraY){
            keyboard.update(event);

            vel += gravity;

            if(host){
                if(keyboard.up) y -= speed;
                if(keyboard.down) y += speed;
                if(keyboard.left) x -= speed;
                if(keyboard.right) x += speed;
                if(keyboard.respawn){
                    x = 100;
                    y = 100;
                    z = -10;
                    vel = 0;
                }
                if(colliding){
                    vel = 0;

                    if(keyboard.jump){
                        vel -= jumpHeight;
                    }
                }
            }else{
                if(colliding){
                    vel = 0;
                }
            }

            z += vel;

            renderX = x+animation.anchorX+cameraX;
            renderY = z+y+animation.anchorY+cameraY;
        }

        SDL_Renderer * render(SDL_Renderer * renderer){
            sprite = animation.showFrame();

            playerSize.x = renderX;
            playerSize.y = renderY;

            SDL_RenderCopy(renderer, sprite, NULL, &playerSize);

            return renderer;
        }

        void end(){
            animation.destroy();
        }
};

#endif
