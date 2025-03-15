class Scene {
private:
    Player player;

    std::vector<GameObject> gameObjects;
    // std::vector<Enemy>* enemies;
    // std::vector<UI>* elementsUI;

    int windowWidth, windowHeight;
    mat3 projection;
    
public:
    Scene(){

    }

    Scene(int width, int height, SDL_Renderer* renderer)
    {
        windowHeight = height;
        windowWidth = width;
        
        player = Player(width, height);
        player.setCamera(Camera());
        player.loadAllAnimations("Test", renderer);

        projection = projection.orthographic(0, width, 0, height);

        gameObjects.emplace_back(renderer, "assets/textures/mario.png");
    }

    void render(SDL_Renderer* renderer){
        for(auto& object : gameObjects){
            object.draw(renderer, player, projection, windowWidth, windowHeight);
        }

        player.updateVertices(projection, windowWidth, windowHeight);
        player.draw(renderer);
    }

    void processInput(){
        // Movement
        const bool *keyStates = SDL_GetKeyboardState(NULL);
        if (keyStates[SDL_SCANCODE_W])
            player.move(UP);
        if (keyStates[SDL_SCANCODE_A])
            player.move(LEFT);
        if (keyStates[SDL_SCANCODE_S])
            player.move(DOWN);
        if (keyStates[SDL_SCANCODE_D])
            player.move(RIGHT);
    }
};