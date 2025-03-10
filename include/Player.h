
#include <Camera.h>
#include <Animator.h>

class Player{
private:
    float movementSpeed = 5.0f;
    Camera cam;
    vec2 pos;
    mat3 model;

    Animation test;
    SDL_FRect boundingBox;

    int count = 0;

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


    void loadAllAnimations(std::string folderPath, SDL_Renderer *renderer){
        test = loadAnimation("assets/animations/Jump/", renderer);
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
                pos.x += movementSpeed;
                break;
            case (RIGHT):
                pos.x -= movementSpeed;
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

        boundingBox = {tX, tY, 100, 100};
    }

    vec2& screenSpace(float width, float height, float x, float y){
        vec2 screen;

        screen.x = (x/2) + (width/2);
        screen.y = -(y/2) + (height/2);

        return screen;
    }


    void draw(SDL_Renderer* renderer){
        int tester = 0;
        if(count >= 5000)
            tester++;
        if(count >= 10000)
            tester++;
        if(count >= 15000)
            tester++;
        if(count >= 30000)
            count = 0;
            
        count++;
        SDL_RenderTexture(renderer, test.sprites[tester], NULL, &boundingBox);
    }
};


