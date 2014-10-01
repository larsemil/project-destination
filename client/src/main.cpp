#include <iostream>
#include <SDL/SDL.h>
#include "GameEngine.hpp"

int main(int argc, char ** argv)
{
    GameEngine* gameEngine = GameEngine::Instance();
    SDL_Rect screenBounds = { 1024, 600, NULL, NULL };

    try
    {
        gameEngine->Initialize(screenBounds);
        gameEngine->Start();
    }
    catch (const char* e)
    {
        std::cout << e << std::endl;
    }
    catch (std::string e)
    {
        std::cout << e << std::endl;
    }

    return 0;
}
