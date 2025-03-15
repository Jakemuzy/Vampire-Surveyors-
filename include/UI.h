enum ScreenType
{
    MAIN, GAME, PAUSE
};

enum ButtonType {
    START, SETTINGS, QUIT
};

struct Image 
{
    vec2 pos;
    SDL_FRect rect;
};

struct TextElement
{
    vec2 pos;
};

struct Button {
    TextElement text;
    ButtonType type;

    SDL_FRect rect;
    float color[4] = {255, 0, 0, 255};

    vec2 pos;
    int offsetNum;
    bool clicked;
};


class UI {
private:
    ScreenType currentScreen;
    float widthUI = 300, heightUI = 150;
    float offset = 10;
public:
    std::vector<Button> buttons;

    UI(int width, int height){

        widthUI = width / 2;
        heightUI = height / 7;

        Button start, settings, quit;

        //Main menu
        start.offsetNum = 4;
        start.type = START;
        start.rect = {(float)(width / 2) - (float)(widthUI / 2), (float)((height * start.offsetNum) / 7) - (float)(heightUI), widthUI, heightUI};
        buttons.push_back(start);

        settings.offsetNum = 6;
        settings.type = SETTINGS;
        settings.rect = {(float)(width / 2) - (float)(widthUI / 2), (float)((height * settings.offsetNum) / 7) - (float)(heightUI), widthUI, heightUI};
        buttons.push_back(settings);

        quit.offsetNum = 7;
        quit.type = QUIT;
        quit.rect = {(float)(width / 2) - (float)(widthUI / 2), (float)((height * quit.offsetNum) / 7) - (float)(heightUI), widthUI, heightUI};
        buttons.push_back(quit);
    }

    void resize(int width, int height){
        widthUI = width / 3;
        heightUI = height / 7;
        for (auto &button : buttons)
        {
            std::cout << width << " " << height << "\n";
            button.rect = {(float)(width / 2) - (float)(widthUI / 2), (float)((height * button.offsetNum) / 7) - (float)(heightUI), widthUI, heightUI};
        }
    }

    void eventHandle(ButtonType bType)
    {

    }

    void refreshElements(){
        buttons.clear();
    }

    void startGame()
    {
        buttons.clear();
    }

    void draw(SDL_Renderer* renderer){
        
        for (auto &element : buttons)
        {
            SDL_SetRenderDrawColor(renderer, element.color[0], element.color[1], element.color[2], element.color[3] ); // Red
            SDL_RenderRect(renderer, &element.rect);
        }
    }
};