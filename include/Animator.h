#include <filesystem>
#include <SDL3_image/SDL_image.h>

namespace fs = std::filesystem;

struct Animation
{
    std::vector<SDL_Texture *> sprites;
    int FPS;
};

struct playerAnimations
{
    Animation walkLeft;
    Animation walkRight;
    Animation walkUp;
    Animation walkDown;
};

struct attackAnimations
{
    Animation standard;
};

Animation loadAnimation(std::string folderPath, SDL_Renderer *renderer)
{
    Animation currentAnim;

    for (const auto &entry : fs::directory_iterator(folderPath))
    {
        if (fs::is_regular_file(entry))
        {
            fs::path filePath = entry.path();
            std::string spriteName = folderPath + filePath.filename().string();

            const char *path = spriteName.c_str();

            SDL_Texture *currentSprite = IMG_LoadTexture(renderer, path);
            if (!currentSprite)
            {
                std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
            }
            SDL_SetTextureScaleMode(currentSprite, SDL_SCALEMODE_NEAREST);      //Optimized for pixel art rendering
            currentAnim.sprites.push_back(currentSprite);
            currentAnim.FPS = 3;
        }
        
    }
    return currentAnim;
}

void loadAllAnimations(){
    return;
}