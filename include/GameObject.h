

class GameObject { 
private:
    vec2 pos;
    std::vector<SDL_Vertex> vertices;

    SDL_Texture *sprite;
    SDL_FRect boundingBox;
    
public:
    GameObject(){

    }

    //Specify world Pos and sprite, also size
    GameObject(SDL_Renderer *renderer, std::string spritePath)
    {

        
        const char* path = spritePath.c_str();

        sprite = IMG_LoadTexture(renderer, "assets/textures/mario.png");
        if (!sprite)
        {
            std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
        }
        
    }

    void draw(SDL_Renderer* renderer, Player& player, mat3& projection, int width, int height){

        mat3 view = player.getCamera().getViewMatrix();
        mat3 modelView = player.getModel();// * view;
        mat3 modelViewProj = modelView * projection;

        vec2 screen = screenSpace(width, height, modelViewProj[0][2], modelViewProj[1][2]);
        float tX = screen.x, tY = screen.y;

        vertices = {
            {{tX - 100, tY - 100}, {0, 0, 255, 255}, {0, 0}},
            {{tX, tY + 100}, {0, 0, 255, 255}, {0, 0}},
            {{tX + 100, tY - 100}, {0, 0, 255, 255}, {0, 0}},
        };

        boundingBox = {tX, tY, 100, 100}; 

        SDL_RenderTexture(renderer, sprite, NULL, &boundingBox);

        //std::cout << tX << " " << tY << "\n";
        //SDL_RenderGeometry(renderer, NULL, &vertices[0], 3, NULL, 0);
    }

    vec2 &screenSpace(float width, float height, float x, float y)
    {
        vec2 screen;

        screen.x = (x / 2) + (width / 2);
        screen.y = -(y / 2) + (height / 2);

        return screen;
    }
};