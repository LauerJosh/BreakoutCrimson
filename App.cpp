#include "App.h"
 
App::App(char *Title, int ScreenWidth, int ScreenHeight, int ScreenBpp)
{
    MainWindow.Create(sf::VideoMode( ScreenWidth, ScreenHeight, ScreenBpp), Title );
 
    MainWindow.SetFramerateLimit(60);
 
    View = MainWindow.GetDefaultView();
 
}
 
App::~App()
{
    // Clean stuff up
}
 
bool App::Init()
{
	//Ball movement.
	ballMoveX = 8;
	ballMoveY = 6;
	setMoveX = 8;
	setMoveY = 6;

	//Brick sprite array dimensions
	h = 6; //Height
	w = 10; //Width
	y = 20; 

	//Other
	lives = 3;
	iScore = 0;
	brickCount = 60;

    // Initlize stuff
	if (!ballImage.LoadFromFile("Ball.png"))
	{
	}
	ballSprite.SetImage(ballImage);
	if (!playerImage.LoadFromFile("Player.png"))
	{
	}
	playerSprite.SetImage(playerImage);

	//Brick Array
	if (!BrickImageRed.LoadFromFile("BrickRed.png"))
    {
        
    }
	for (int j = 0; j < w; j++)
    {
		for (int i = 0; i < h; i++)
		{
			 BrickSpriteRed[j][i].SetImage(BrickImageRed);
			// Get the sprite's dimensions
			float Width  = BrickSpriteRed[j][i].GetSize().x;
			float Height = BrickSpriteRed[j][i].GetSize().y;
   
			BrickSpriteRed[j][i].SetPosition(160 + (i * 80), (y)); //First number sets horizontal position for each block, creating the line. Second number just sets the height. I did a seperate loop for each colour, increasing the height by 10.
		}
		y += 10; //Increments to the next row of bricks
	}
	
	//Brick sprite array
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			brickSpriteRed[j][i] = true;
		}
	}
	ballSprite.SetPosition(100, 200);

	//Rects
	ballRect = sf::Rect<float>();
	playerRect = sf::Rect<float>();
	for (int j = 0; j < w; j++)
    {
		for (int i = 0; i < h; i++)
		{
			brickRect[j][i] = sf::Rect<float>();
		}		
	}

	//Sound files
	if (!DeadBuffer.LoadFromFile("Dead.wav"))
	{
		// Error....
	}
	DeadSound.SetBuffer(DeadBuffer);
	if (!brickHitBuffer.LoadFromFile("Hit bricks.wav"))
	{
		// Error....
	}
	brickHitSound.SetBuffer(brickHitBuffer);
	if (!paddleHitBuffer.LoadFromFile("Hit bat.wav"))
	{
		// Error....
	}
	paddleHitSound.SetBuffer(paddleHitBuffer);
    return true;
}
 
void App::Update()
{
    //Update stuff
}
 
void App::Draw()
{
     MainWindow.Clear();
     MainWindow.SetView( View );

    //Draw stuff needed
	MainWindow.Draw(ballSprite); 
	MainWindow.Draw(playerSprite);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			//Checks to see if the bricks are still there before drawing	
			MainWindow.Draw(BrickSpriteRed[j][i]);				
		}
	}
    MainWindow.Display();
}
 
void App::HandleEvents()
{
     const sf::Input& Input = MainWindow.GetInput();
 
     if( Event.Type == sf::Event::Closed )
          MainWindow.Close();
 
     if( ( Event.Type == sf::Event::KeyPressed ) && ( Event.Key.Code == sf::Key::Escape ) )
          MainWindow.Close();
	if (Event.Type == sf::Event::MouseMoved)
	{
		playerSprite.SetPosition(MainWindow.GetInput().GetMouseX()-51, 550);
	}
    ballSprite.Move(ballMoveX, ballMoveY);
	
	/////////////////Using sprites to define rects////////////////////

	//Ball
	ballRect.Left = ballSprite.GetPosition().x;
	ballRect.Right = ballSprite.GetPosition().x + ballSprite.GetSize().x;
	ballRect.Top= ballSprite.GetPosition().y;
	ballRect.Bottom = ballSprite.GetPosition().y + ballSprite.GetSize().y;

	//Player
	playerRect.Left = playerSprite.GetPosition().x;
	playerRect.Right = playerSprite.GetPosition().x + playerSprite.GetSize().x;
	playerRect.Top = playerSprite.GetPosition().y;
	playerRect.Bottom = playerSprite.GetPosition().y + playerSprite.GetSize().y;

	//Brick array
	for (int j = 0; j < w; j++)
    {
		for (int i = 0; i < h; i++)
		{
			brickRect[j][i].Left = BrickSpriteRed[j][i].GetPosition().x;
			brickRect[j][i].Right = BrickSpriteRed[j][i].GetPosition().x + BrickSpriteRed[j][i].GetSize().x;
			brickRect[j][i].Top = BrickSpriteRed[j][i].GetPosition().y;
			brickRect[j][i].Bottom = BrickSpriteRed[j][i].GetPosition().y + BrickSpriteRed[j][i].GetSize().y;
		}
	}

	////collision detection
	//Ball and Paddle
	if (ballRect.Intersects(playerRect))
	{
		ballSprite.Move(0,0);
		ballSprite.SetPosition(ballOldX, ballOldY);
		//Redraw RECT
		ballRect.Left = ballSprite.GetPosition().x;
		ballRect.Right = ballSprite.GetPosition().x + ballSprite.GetSize().x;
		ballRect.Top= ballSprite.GetPosition().y;
		ballRect.Bottom = ballSprite.GetPosition().y + ballSprite.GetSize().y;
		if (ballRect.Left > playerRect.Right)
		{
			ballMoveX = -ballMoveX;			
		}
		if (ballRect.Right < playerRect.Left)
		{
			ballMoveX = -ballMoveX;			
		}
		if (ballRect.Top < playerRect.Bottom)
		{
			ballMoveY = -ballMoveY;			
		}
		if (ballRect.Bottom > playerRect.Top)
		{
			ballMoveY = -ballMoveY;			
		}
		paddleHitSound.Play();
	}
	
	//Ball and brick collision
	for (int i = 0; i<h; i++)
	{
		for (int j = 0; j<w; j++)
		{
			if (ballRect.Intersects(brickRect[j][i]))
			{
				ballSprite.Move(0,0);
				ballSprite.SetPosition(ballOldX, ballOldY);

				//Redraw RECT
				ballRect.Left = ballSprite.GetPosition().x;
				ballRect.Right = ballSprite.GetPosition().x + ballSprite.GetSize().x;
				ballRect.Top= ballSprite.GetPosition().y;
				ballRect.Bottom = ballSprite.GetPosition().y + ballSprite.GetSize().y;

				if (ballRect.Left > brickRect[j][i].Right)
				{
					ballMoveX = -ballMoveX;
					BrickSpriteRed[j][i].SetPosition(-1000,-1000);
				}
				if (ballRect.Right < brickRect[j][i].Left)
				{
					ballMoveX = -ballMoveX;
					BrickSpriteRed[j][i].SetPosition(-1000,-1000);
				}
				if (ballRect.Top < brickRect[j][i].Bottom)
				{
					ballMoveY = -ballMoveY;
					BrickSpriteRed[j][i].SetPosition(-1000,-1000);
				}
				if (ballRect.Bottom > brickRect[j][i].Top)
				{
					ballMoveY = -ballMoveY;
					BrickSpriteRed[j][i].SetPosition(-1000,-1000);
				}
				iScore += 5;
				brickHitSound.Play();
				brickCount--;
			}			
		}				
	}

	//Ball and wall collision 
	if (ballSprite.GetPosition().x + ballSprite.GetSize().x >= 800)
	{
		ballMoveX = -ballMoveX;
	}
	if (ballSprite.GetPosition().x + ballSprite.GetSize().x <= 15)
	{
		ballMoveX = -ballMoveX;
	}
	if (ballSprite.GetPosition().y + ballSprite.GetSize().y >= 600)
	{
		lives--;
		ballSprite.SetPosition(100, 200);
		ballSprite.Move(setMoveX, setMoveY);
		ballMoveX = setMoveX;
		ballMoveY = setMoveY;
		DeadSound.Play();		
	}
	if (ballSprite.GetPosition().y + ballSprite.GetSize().y <= 15)
	{
		ballMoveY = -ballMoveY;
	}

	ballOldX = ballSprite.GetPosition().x;
	ballOldY = ballSprite.GetPosition().y;

	if (lives <= 0)
	{	
		MainWindow.Close();
		cout<<"Your score :"<<iScore<<endl;
		system("PAUSE");
	}
	if (brickCount <= 0)
	{
		MainWindow.Close();
		cout<<"Well done! You win!"<<endl;
		system("PAUSE");
	}
}
 
void App::Run()
{
    while(MainWindow.IsOpened())
    {
        while(MainWindow.GetEvent(Event))
        {
            HandleEvents();
        }
        Update();
        Draw();
    }
}
