#include <raylib.h>
#include<vector>
#include "HighScore.cpp"

bool backgroundChanged = false;
bool isPaused = false;
bool isMusicPaused = false;
enum GameState { MENU, PLAYING, GAME_OVER, SHOP, INSTRUCTIONS, EXIT};
enum BikeType {SCOOTY, NINJA_H2R};

class Vehicle 
{
protected:
    int speed;
    Texture2D image;

public:
    Vector2 position;
    virtual void draw() = 0;
    virtual void Update() = 0;
    virtual Rectangle GetRect() = 0;

    virtual ~Vehicle() {}
};

class cars : public Vehicle
{
public: 
    void draw() override;
    void Update() override;
    cars(float StartX, float StartY);
    Rectangle GetRect() override;
};

class bike : public Vehicle 
{
    Texture2D normalBike;
    Texture2D boostBike;
    BikeType currentBike;
    Texture2D normalScooty;
    Texture2D boostScooty;
    Texture2D normalNinja;
    Texture2D boostNinja;
    
public:
    void draw() override;
    bike();
    void MoveLeft();
    void MoveRight();
    Rectangle GetRect() override;
    void Update() override; 
    void SetBike(BikeType bikeType);
    BikeType GetCurrentBike();
    int GetSpeed();
};

class Shop 
{
    Texture2D shopMenu;
public:
    Shop();
    void Draw(BikeType selectedBike);
    bool HandleInput(BikeType& currentBike);
};

class Game{
    bool gameEnded = false;
public: 
    bike b1;
    vector<cars> carList; 
    Shop shop;
    HighScore ScoreManager;
    Game();
    void InputHandling();
    void Draw();
    void update();
    bool End();
    bool DrawButton(const char* text, int x, int y, int fontSize, Sound buttonSound, Vector2 mousePos, GameState &currentState, GameState targetState);
    void Reset();
    int score = 0;
    bool newMapSoundPlayed = false;
    bool IsNewHighScore = false;
    BikeType selectedBike = SCOOTY;
};

// cars functions definitions
cars :: cars(float StartX, float StartY)
{
    image = LoadTexture("graphics/car.png");
    position = {StartX, StartY};
    speed = 7;
}

void cars :: draw()
{
    DrawTexture(image, position.x, position.y, WHITE);
}

void cars :: Update()
{
    if(position.y > GetScreenHeight())
    {
        int RandomIndex;

        if(backgroundChanged)
        {
            RandomIndex = GetRandomValue(85, GetScreenWidth() - 128);
        }
        else
        {
         RandomIndex = GetRandomValue(30, GetScreenWidth() - 50);
        }

        position.y = -100;
        position.x = RandomIndex;
    }
    else if(IsKeyDown(KEY_SPACE))
    {
        position.y += speed + 4;
    }
    else
    {
        position.y += speed;
    }
}

Rectangle cars :: GetRect()
{
    return{position.x, position.y, (float)image.width, (float)image.height};
}

// bike definitions
bike :: bike()
{
    normalScooty = LoadTexture("graphics/scooty.png");
    boostScooty = LoadTexture("graphics/boost-scooty.png");
    
    normalNinja = LoadTexture("graphics/bike.png");
    boostNinja = LoadTexture("graphics/boost-bike.png");
    
    currentBike = SCOOTY;
    SetBike(SCOOTY);
    position = {GetScreenWidth() / 2.0, GetScreenHeight() - 110.0 };
}

void bike :: SetBike(BikeType bikeType)
{
    currentBike = bikeType;
    
    if(bikeType == SCOOTY)
    {
        normalBike = normalScooty;
        boostBike = boostScooty;
        speed = 5;
    }
    else if(bikeType == NINJA_H2R)
    {
        normalBike = normalNinja;
        boostBike = boostNinja;
        speed = 6; 
    }
    
    image = normalBike;
}

void bike :: draw()
{
    float rotation = 0;

    if(IsKeyDown(KEY_LEFT) && !isPaused)
    {
        rotation = -10;
    }

    if(IsKeyDown(KEY_RIGHT) && !isPaused)
    { 
        rotation = 10;
    }
    
    if(IsKeyDown(KEY_SPACE))
    {
        DrawTextureEx(image, position, rotation, 1.0f, YELLOW);
    }

    else 
    {
        DrawTextureEx(image, position, rotation, 1.0f, YELLOW);
    }
    
    if(IsKeyDown(KEY_SPACE) && !isPaused)
    {
        image = boostBike;
    }
    else 
    {
        image = normalBike;
    }
}

void bike :: Update()
{
    
}

void bike :: MoveLeft()
{
    if(backgroundChanged)
    {
        if(position.x > 91)
        {
          position.x -= speed;
        }
    }
    else
    {
        if(position.x > 35)
        {
          position.x -= speed;
        }
    }
}

void bike :: MoveRight()
{
    if(backgroundChanged)
    {
        if(position.x < GetScreenWidth() - image.width - 91)
        {
          position.x += speed;
        }
    }
    else
    {
        if(position.x < GetScreenWidth() - image.width - 35)
        {
          position.x += speed;
        }
    }
}

BikeType bike ::  GetCurrentBike() 
{
     return currentBike; 
}

int bike :: GetSpeed()
{
    return speed; 
}

Rectangle bike :: GetRect()
{
    return {position.x, position.y, (float)image.width, (float)image.height};
}

// Shop class definitions
Shop :: Shop()
{
    shopMenu = LoadTexture("graphics/menu-2.png");
    
}

void Shop :: Draw(BikeType selectedBike)
{
    DrawTexture(shopMenu, 0, 0, WHITE);
    DrawRectangle(0, 0, GetScreenWidth() , GetScreenHeight(), Fade(BLACK, 0.3f));
    Color scootyColor;

    if(selectedBike == SCOOTY)
    {
        scootyColor = GREEN;
    }
    else
    {
        scootyColor = DARKGRAY;
    }

    DrawRectangle(50, 190, 290, 80, scootyColor);
    DrawRectangleLines(50, 190, 290, 80, WHITE);
    DrawText("SCOOTY", 60, 200, 20, SKYBLUE);
    DrawText("Speed: 5", 60, 230, 16, WHITE);

    if(selectedBike == SCOOTY)
    {
        DrawText("SELECTED", 220, 200, 16, YELLOW);
    }
    
    Color ninjaColor;

    if(selectedBike == NINJA_H2R)
    {
        ninjaColor = GREEN;
    }

    else
    {
        ninjaColor = DARKGRAY;
    }

    DrawRectangle(50, 300, 290, 80, ninjaColor);
    DrawRectangleLines(50, 300, 290, 80, WHITE);
    DrawText("NINJA H2R", 60, 310, 20, SKYBLUE);
    DrawText("Speed: 7", 60, 340, 16, WHITE);

    if(selectedBike == NINJA_H2R)
    {
        DrawText("SELECTED", 220, 320, 16, YELLOW);
    }
}

bool Shop :: HandleInput(BikeType& currentBike)
{
    if(IsKeyPressed(KEY_ONE))
    {
        currentBike = SCOOTY;
        return true;
    }
    
    if(IsKeyPressed(KEY_TWO))
    {
        currentBike = NINJA_H2R;
        return true;
    }
    
    return false;
}

// game functions definitions
Game :: Game()
{
    carList.push_back(cars(100, -135));
    carList.push_back(cars(175, -320));
    carList.push_back(cars(250, -510));
    carList.push_back(cars(300, -655));
}

void Game :: update()
{
    for(int i=0; i < carList.size(); i++)
    {
       carList[i].Update();
    }
}

void Game :: Draw()
{
    b1.draw();

    for(int i=0; i < carList.size(); i++)
    {
        carList[i].draw();
    } 

    DrawRectangle(20, 20, 118, 30, BLACK);
    DrawRectangleLines(20, 20, 118, 30, SKYBLUE);
    DrawText(TextFormat("Score: %d", score/10), 30, 27, 15, SKYBLUE);
    
    string bikeText;
    
    if(selectedBike == SCOOTY)
    {
        bikeText = "Scooty";
    }
    else
    {
        bikeText = "Ninja H2R";
    }
    DrawRectangle(260, 24, 118, 30, BLACK);
    DrawRectangleLines(260, 24, 118, 30, GREEN);
    DrawText(bikeText.c_str(), 300, 32, 13, GREEN);
}

void Game :: InputHandling()
{
    if(IsKeyDown(KEY_RIGHT))
    {
        b1.MoveRight();
    }
    else if(IsKeyDown(KEY_LEFT))
    {
        b1.MoveLeft();
    }
}


bool Game :: DrawButton(const char* text, int x, int y, int fontSize, Sound buttonSound, Vector2 mousePos, GameState &currentState, GameState targetState)
{
    int width = MeasureText(text, fontSize);
    Rectangle buttonRect = { x - 10, y - 10, width + 20, fontSize + 20 };

    // Hover effect
    Color buttonColor;
	if(CheckCollisionPointRec(mousePos, buttonRect))
	{
		buttonColor = ORANGE;
	}
	else
	{
		buttonColor = RED;
	}

    DrawRectangle(x - 10, y - 10, width + 20, fontSize + 20, buttonColor);
    DrawText(text, x, y, fontSize, WHITE);

    // check collison
    if (CheckCollisionPointRec(mousePos, buttonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        PlaySound(buttonSound);
        currentState = targetState;
        return true;
    }

    return false;
}


bool Game :: End()
{
    for(int i = 0; i < carList.size(); i++)
    {
        if(CheckCollisionRecs(b1.GetRect(), carList[i].GetRect()))
        {
            gameEnded = true;
            int finalScore = score / 10;
            IsNewHighScore = ScoreManager.IsNewHighScore(finalScore);
            ScoreManager.CheckScore(finalScore);
        }
    }
   return gameEnded;
}

void Game :: Reset()
{
    b1.position = {GetScreenWidth() / 2.0, GetScreenHeight() - 110.0 };
    b1.SetBike(selectedBike); 
    carList.clear();
    carList.push_back(cars(100, -135));
    carList.push_back(cars(175, -320));
    carList.push_back(cars(250, -510));
    carList.push_back(cars(300, -655));
    gameEnded = false;
    score = 0;
    newMapSoundPlayed = false;
    IsNewHighScore = false;
}

int main() {
    int screenWidth = 390;
    int screenHeight = 650;
    Vector2 bgpos = {-350,-600};
    InitWindow(screenWidth, screenHeight, "SpeedRush 2D");

    Texture2D background1 = LoadTexture("graphics/road-1.png");
    Texture2D background2 = LoadTexture("graphics/desert.png");
    Texture2D menuPage = LoadTexture("graphics/menu-2.png");

    Texture2D gameOver = LoadTexture("graphics/game_over.png");
    Texture2D background = background1;

    InitAudioDevice();  
    Music BackgroundMusic = LoadMusicStream("sounds/background_music.ogg");
    SetMusicVolume(BackgroundMusic, 0.3f);
    Sound Bike = LoadSound("sounds/race.wav");
    SetSoundVolume(Bike, 0.5f);
    Sound GameOver = LoadSound("sounds/game_over.wav");
    SetSoundVolume(GameOver, 0.5f);
    Sound NewMap = LoadSound("sounds/new-map.wav");
    Sound buttonPressed = LoadSound("sounds/beep.wav");
    
    GameState currentState = MENU;
    
    Game game;
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) 
    {
        if (!IsMusicStreamPlaying(BackgroundMusic) && !isMusicPaused)
            {
                PlayMusicStream(BackgroundMusic);
            }
            UpdateMusicStream(BackgroundMusic);

        if(IsKeyPressed(KEY_M))
        {
           PauseMusicStream(BackgroundMusic);
           isMusicPaused = !isMusicPaused;
        }

        if (IsKeyPressed(KEY_P)) 
        {
            isPaused = !isPaused;
            PlaySound(buttonPressed);  

            if (isPaused) 
            {
                PauseSound(Bike); 
            } 
            else 
            {
                ResumeSound(Bike); 
            }
        }
            if (currentState == MENU) 
            {

                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) 
                {
                    PlaySound(buttonPressed);
                    currentState = PLAYING;
                    game.Reset();
                    PlaySound(Bike);
                }

                if (IsKeyPressed(KEY_E)) 
                {
                    break;
                }

                if(IsKeyPressed(KEY_S))
                {
                    PlaySound(buttonPressed);
                    currentState = SHOP;
                }
            }
        
        else if (currentState == SHOP)
        {
            if(game.shop.HandleInput(game.selectedBike))
            {
                PlaySound(buttonPressed);
            }
        }

        else if (currentState == PLAYING) 
    {

        PauseMusicStream(BackgroundMusic);

        if (!isPaused)
        {
            if(IsKeyDown(KEY_SPACE))
            {
                game.score+=2;
            }
            else
            {
                game.score++;
            }

            if(IsKeyDown(KEY_SPACE))
            {
                bgpos.y += 9;  
            }
            else
            {
                bgpos.y += 5;
            }

            if(bgpos.y > GetScreenHeight() - 600)
            {
                bgpos.y = -600;
            }

            game.InputHandling();
            game.update();

            if (!IsSoundPlaying(Bike))
            {
                PlaySound(Bike);  
            }

            if(game.End()) 
            {
                currentState = GAME_OVER;
                PlaySound(GameOver);
                StopSound(Bike);
            }
        }
    }

        else if (currentState == GAME_OVER) 
        {
            if (IsKeyPressed(KEY_Y)) 
            {
                PlaySound(buttonPressed);
                currentState = MENU;
                game.Reset();
                background = background1;
                backgroundChanged = false;
            }

            if(IsKeyPressed(KEY_N))
            {
                break;
            }

            if (IsKeyPressed(KEY_ESCAPE)) 
            {
                break;
            }
        }

        else if(currentState == EXIT)
        {
            break;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (currentState == MENU) 
        {
            DrawTextureEx(menuPage, {0,0}, 0, 1.0f, WHITE);
            const char* titleText = "SpeedRush 2D";
           const char* playText = "Press To Start";
           const char* shopText = "Press To Shop";
           const char* instructionsText = "Instructions";
           const char* exitText = "Press To Exit";

            int titleFontSize = 45;
			int titleWidth = MeasureText(titleText, titleFontSize);
			int titleX = 45;
			int titleY = 40;
			DrawText(titleText, titleX, titleY, titleFontSize, GOLD);
			DrawLine(titleX, titleY + 55, titleWidth, titleY + 55, LIGHTGRAY);

           int TextX = 112;

           // start button 
           game.DrawButton(playText, TextX, 180, 20, buttonPressed, GetMousePosition(), currentState, PLAYING);

           // shop button
           game.DrawButton(shopText, TextX, 280, 20, buttonPressed, GetMousePosition(), currentState, SHOP);

           // instructions button
           game.DrawButton(instructionsText, TextX, 380, 20, buttonPressed, GetMousePosition(), currentState, INSTRUCTIONS);

           // exit button
            game.DrawButton(exitText, TextX, 480, 20, buttonPressed, GetMousePosition(), currentState, EXIT);
        }

        else if(currentState == INSTRUCTIONS)
        {
            DrawTextureEx(menuPage, {0,0}, 0, 1.0f, WHITE);
            DrawRectangle(0, 0, GetScreenWidth() , GetScreenHeight(), Fade(BLACK, 0.3f));
            DrawText("INSTRUCTIONS", 90, 50, 30, GOLD);
            DrawText("Use LEFT and RIGHT arrow keys to move the bike.", 10, 120, 15, LIGHTGRAY);
            DrawText("Press SPACE to boost your speed.", 10, 160, 15, LIGHTGRAY);
            DrawText("Avoid the cars on the road.", 10, 200, 15, LIGHTGRAY);
            DrawText("Reach a score of 150 to unlock the desert \n background.", 10, 240, 15, LIGHTGRAY);
            DrawText("Press P to pause the game.", 10, 290, 15, LIGHTGRAY);

            game.DrawButton("Back to Menu", 150, 550, 15, buttonPressed, GetMousePosition(), currentState, MENU);
        }
        
        else if (currentState == SHOP)
        {
            game.shop.Draw(game.selectedBike);
            DrawText("Select your bike:", 50, 150, 20, GOLD);
            DrawText("Press 1 for Scooty", 50, 470, 20, LIGHTGRAY);
            DrawText("Press 2 for Ninja H2R", 50, 500, 20, LIGHTGRAY);
            game.DrawButton("Back to Menu", 150, 570, 15, buttonPressed, GetMousePosition(), currentState, MENU);
        }

        else if (currentState == PLAYING) 
        {
            if(game.score > 150*10 && !backgroundChanged)
            {
                background = background2;
                backgroundChanged = true;

                if(!game.newMapSoundPlayed)
                {
                    PlaySound(NewMap);
                    game.newMapSoundPlayed = true;
                }
            }

            DrawTexture(background, -350, bgpos.y, WHITE);
            DrawTexture(background, -350, bgpos.y - GetScreenHeight(), WHITE);
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.25f));

            if (isPaused)
            {
                DrawText("PAUSED", GetScreenWidth()/2 - 50, GetScreenHeight()/2 - 10, 30, WHITE);
            }

            if(!backgroundChanged && game.score/10 < 150)
            {
                DrawText("Reach 150 to unlock Desert", 25, 60, 11, ORANGE);
            }

            else if(backgroundChanged)
            {
                DrawText("DESERT UNLOCKED!", 24, 60, 12, ORANGE);
            }

            DrawText("Press P to pause", 25, 80, 11, LIGHTGRAY);

            if(IsKeyDown(KEY_SPACE) && !isPaused)
            {
                DrawText("boost active", 158, GetScreenHeight() - 40, 14, RED);
            }

            else
            {
                DrawText("space to boost", 150, GetScreenHeight() - 40, 14, SKYBLUE);
            }

            game.Draw();
        }

        else if (currentState == GAME_OVER) 
        {
             ClearBackground(WHITE);
             DrawTexture(gameOver, 0, 0, WHITE);
             DrawRectangle(GetScreenWidth()/2 - 90, 10, 180, 3, GOLD);
             DrawRectangle(GetScreenWidth()/2 - 90, 40, 180, 3, GOLD);
            
             DrawCircle(GetScreenWidth()/2 - 95, 26, 5, GOLD);
             DrawCircle(GetScreenWidth()/2 + 95, 26, 5, GOLD);
             DrawText(TextFormat("Score: %d", game.score/10), 
             GetScreenWidth()/2 - 52, 16, 20, SKYBLUE);

             DrawText(TextFormat("High Score: %d", game.ScoreManager.getHighScore()), 
                      10, 100, 18, GOLD);

             if(game.IsNewHighScore)
             {
                 DrawText("NEW HIGH SCORE!", 10, 70, 16, RED);
             }
        }
        
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(background1);
    UnloadTexture(background2);
    UnloadSound(Bike);
    UnloadSound(GameOver);
    UnloadSound(NewMap);
    UnloadSound(buttonPressed);
    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}