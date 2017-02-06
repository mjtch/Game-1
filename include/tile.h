
class Tile {
    public:
        SDL_Texture * sprite;
        bool collidable = true;
        int renderW = 55;
        int renderH = 65;

        void init(SDL_renderer * renderer, bool _collidable, int _renderW, int _renderH){
            collidable = true;
            renderW = _renderW;
            renderH = _renderH;
        }

        void render(SDL_Renderer * renderer, int renderX, int renderY){
        }

        double onCollisionZ(double playerX, double playerY, double tileX, double tileY){
        }
};
