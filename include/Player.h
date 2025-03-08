
#include <Camera.h>

class Player{
private:
    float movementSpeed = 5.0f;
    Camera cam;
    vec2 pos;
    mat3 model;

    SDL_Rect boundingBox;
    std::vector<SDL_Vertex> vertices;
public:
    Player(){
        movementSpeed = 0.05f;
        pos.x = 0;
        pos.y = 0;
    }
    Player(int width, int height)
    {
        movementSpeed = 0.05f;
        pos.x = 0; 
        pos.y = 0;

    }

    void setCamera(Camera& camera){
        cam = camera;
    }

    Camera& getCamera(){
        return cam;
    }

    void move(directions direction)
    {
        switch(direction){
            case (UP):
                pos.y -= movementSpeed;
                break;
            case (DOWN):
                pos.y += movementSpeed;
                break;
            case (LEFT):
                pos.x -= movementSpeed;
                break;
            case (RIGHT):
                pos.x += movementSpeed;
                break;
            default:
                break;
        }
        model[0][2] = pos.x;
        model[1][2] = pos.y;
        cam.move(pos);
    }

    vec2 getPos(){
        return pos;
    }

    mat3& getModel(){
        return model;
    }

    void updateVertices(mat3& projection, int width, int height){
        mat3 view = cam.getViewMatrix();
        mat3 modelView = model * view;
        mat3 modelViewProj = modelView * projection;

        vec2 screen = screenSpace(width, height, modelViewProj[0][2], modelViewProj[1][2]);
        float tX = screen.x, tY = screen.y;

        vertices = {
            {{tX - 100, tY - 100}, {255, 0, 0, 255}, {0, 0}},
            {{tX, tY + 100}, {255, 0, 0, 255}, {0, 0}},
            {{tX + 100, tY - 100}, {255, 0, 0, 255}, {0, 0}}
        };
    }

    vec2& screenSpace(float width, float height, float x, float y){
        vec2 screen;

        screen.x = (x/2) + (width/2);
        screen.y = -(y/2) + (height/2);

        return screen;
    }


    std::vector<SDL_Vertex>& getVertices()
    {
        return vertices;
    }

    void draw(SDL_Renderer* renderer){
        SDL_RenderGeometry(renderer, NULL, &vertices[0], vertices.size(), NULL, 0);
    }
};


