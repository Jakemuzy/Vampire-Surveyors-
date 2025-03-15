#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#include <vector>
#include <iostream>

#include <Player.h>
#include <GameObject.h>
#include <UI.h>
#include <Scene.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
int windowWidth = 960, windowHeight = 540;
//Player player(windowWidth, windowHeight);
UI elements(windowWidth, windowHeight);
Scene* test = nullptr;
//GameObject test;

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

    //player.setCamera(Camera());
    //player.loadAllAnimations("Test", renderer);
    //test = GameObject(renderer, "assets/textures/mario.png");

    return SDL_APP_CONTINUE; 
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT || event->key.key == 27)
    {
        return SDL_APP_SUCCESS; 
    }

    if(event->type == SDL_EVENT_WINDOW_RESIZED){
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        elements.resize(windowWidth, windowHeight);
    }

    //UI Handling

    if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        vec2 mousePos;
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        for(auto& UI : elements.buttons){
            
            if (mousePos.x < UI.rect.x + UI.rect.w && mousePos.x > UI.rect.x && mousePos.y < UI.rect.y + UI.rect.h && mousePos.y > UI.rect.y)
            {
                UI.color[0] = 0;
                UI.color[1] = 255;
                UI.clicked = true;
            }
            else 
            {
                continue;
            }
               
            if(UI.type == QUIT){
                return SDL_APP_SUCCESS;
            }
            else if (UI.type == START){
                std::cout << "start \n";
                elements.startGame();
                test = new Scene(windowWidth, windowHeight, renderer);
                break;
            }
                
        }
        
    } else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        for (auto &UI : elements.buttons)
        {
            UI.color[0] = 255;
            UI.color[1] = 0;
            UI.clicked = false;
        }
    }

    return SDL_APP_CONTINUE; 
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    

    /* clear the window to the draw color. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 
    SDL_RenderClear(renderer);
    

    if(test!= nullptr){
        test->processInput();
        test->render(renderer);
    }
    

    elements.draw(renderer);

    //player.updateVertices(projection, windowWidth, windowHeight);
    //player.draw(renderer);

    //test.draw(renderer, player, projection, windowWidth, windowHeight);


    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE; 
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}