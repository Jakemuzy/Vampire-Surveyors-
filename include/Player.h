
#include <Camera.h>
#include <iostream>
#include <vector>
#include <SDL3/SDL.h>

class Player{
private:
    float movementSpeed = 5.0f;
    Camera cam;
    vec2 pos;
    std::vector<SDL_Vertex> vertices;
public:
    Player(){
        movementSpeed = 0.5f;
        pos.x = 500;
        pos.y = 300;
    }

    void move(directions direction){
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
        std::cout << pos.x << " " << pos.y << "\n";
    }

    vec2 getPos(){
        return pos;
    }
};