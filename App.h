#ifndef APP_H
#define APP_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/Audio.hpp>
using namespace std;

class App
{
private:
    sf::Event            Event;        // The event
    sf::View            View;          // The view
    sf::RenderWindow        MainWindow;     // The render window
	sf::Image ballImage; //Ball picture
	sf::Image playerImage; //Player picture
	sf::Image BrickImageRed;
	sf::Sprite BrickSpriteRed[10][6];
	sf::Sprite ballSprite; //Ball sprite
	sf::Sprite playerSprite; //Player sprite
	sf::SoundBuffer DeadBuffer;
	sf::SoundBuffer brickHitBuffer;
	sf::SoundBuffer paddleHitBuffer;
	sf::Sound DeadSound;
	sf::Sound brickHitSound;
	sf::Sound paddleHitSound;
	sf::Rect<float> ballRect;
	sf::Rect<float> playerRect;
	sf::Rect<float> brickRect[10][6];
	bool brickSpriteRed[10][6];
	float ballMoveX; //X movement for ball
	float ballMoveY; //Y movement for ball
	int setMoveX;
	int setMoveY;
	int ballOldX;
	int ballOldY;
	int iScore;
	int brickCount;
	int lives;	

	//Used for brick sprite array
	int h;
	int w;
	int y;		

public:
 
    App( char* Title,                // The constructor
         int   ScreenWidth, 
         int   ScreenHeight,
         int   ScreenBpp );
	
    ~App();                        // The destructor
	bool PixelPerfectTest(const sf::Sprite& Object1 ,const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);
    bool Init();                    // Initializes everything not in the constructor
    void HandleEvents();                // Handles input from the player
    void Draw();                    // Draws the scene
    void Update();                    // Updates variables, game object, etc.
    void Run();
};
 
#endif
