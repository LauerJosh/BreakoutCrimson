#include "App.h"
int main()
{
    App Game("Arkanoid", 800, 600, 32);
    if(!Game.Init())
    {
        printf("Could not initialize the game. Please restart the program or contact the game creator."); //Not necessary, but still useful. 
        return 1;
    }
    else
    {
        Game.Run();
    }
    return 0;
}
