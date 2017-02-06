#ifndef keys_h
#define keys_h

class Keys
{
    public:
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        bool jump = false;
        bool respawn = false;

        void update(SDL_Event event){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_SPACE:
                            jump = true; break;
                        case SDLK_a:
                            left = true; break;
                        case SDLK_d:
                            right = true; break;
                        case SDLK_w:
                            up = true; break;
                        case SDLK_s:
                            down = true; break;
                        case SDLK_r:
                            respawn = true; break;
                    }
                break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_SPACE:
                            jump = false; break;
                        case SDLK_a:
                            left = false; break;
                        case SDLK_d:
                            right = false; break;
                        case SDLK_w:
                            up = false; break;
                        case SDLK_s:
                            down = false; break;
                        case SDLK_r:
                            respawn = false; break;
                    }
                break;
            }

            return;
        }
};

#endif
