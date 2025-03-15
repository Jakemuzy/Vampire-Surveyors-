#include <jml.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

enum directions {
    UP, DOWN, LEFT, RIGHT
};


/* Implement, model matrix, view matrix, projection matrix, and then screenspace transform*/
class Camera{
private:
    vec2 pos;
    mat3 view;
    int windowWidth, windowHeight;

public:
    Camera()
    {
        view[0][2] = 0;
        view[1][2] = 0;
    }

    Camera(int width, int height){

    }

    void move(vec2 newPos)
    {
        pos = newPos;
        view[0][2] = newPos.x;
        view[1][2] = newPos.y;
    }

    vec2& getPos(){
        return pos;
    }

    // Inverts so moves the world while camera stays at the origin 
    mat3 getViewMatrix(){
        return view.inverse();
    }

    void Camera::DrawCameraViewport(SDL_Renderer* renderer)
    {

    }
};