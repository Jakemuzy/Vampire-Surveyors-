#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#include <vector>
#include <iostream>

#include <Player.h>
#include <GameObject.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
int windowWidth = 960, windowHeight = 540;
Player player(windowWidth, windowHeight);
GameObject test;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Vampire-Survivors", "1.0", "com.vampire-survivors");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Vampire-Survivors", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    player.setCamera(Camera());
    test = GameObject(renderer, "assets/textures/mario.png");

    return SDL_APP_CONTINUE; 
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT || event->key.key == 27)
    {
        return SDL_APP_SUCCESS; 
    }

    if (event->type == SDL_WINDOW_RESIZABLE){
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    }
    
    return SDL_APP_CONTINUE; 
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    //Movement
    const bool* keyStates = SDL_GetKeyboardState(NULL);
    if(keyStates[SDL_SCANCODE_W])
        player.move(UP);
    if (keyStates[SDL_SCANCODE_A])
        player.move(LEFT);
    if(keyStates[SDL_SCANCODE_S])
        player.move(DOWN);
    if (keyStates[SDL_SCANCODE_D])
        player.move(RIGHT);
    

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    mat3 projection;
    projection = projection.orthographic(0, windowWidth, 0, windowHeight);

    player.updateVertices(projection, windowWidth, windowHeight);
    player.draw(renderer);

    test.draw(renderer, player, projection, windowWidth, windowHeight);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE; 
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}