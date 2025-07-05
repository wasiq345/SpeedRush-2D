#include <raylib.h>
#include <iostream>
#include<vector>
using namespace std;

bool backgroundChanged = false;

class Vehicle {
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

class cars : public Vehicle {
public: 
    void draw() override;
    void Update() override;
    cars(float StartX, float StartY);
    Rectangle GetRect() override;
};

class bike : public Vehicle {
    Texture2D normalBike;
    Texture2D boostBike;
public:
    void draw() override;
    bike();
    void MoveLeft();
    void MoveRight();
    Rectangle GetRect() override;
    void Update() override; 
};

class Game{
    bool gameEnded = false;
public: 
    bike b1;
    vector<cars> carList; 
    Game();
    void InputHandling();
    void Draw();
    void update();
    bool End();
    void Reset();
    int score =0;
    bool newMapSoundPlayed = false;
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
    normalBike = LoadTexture("graphics/bike-1.png");
    boostBike = LoadTexture("graphics/bike-2.png");
    speed = 5;
    position = {GetScreenWidth() / 2.0, GetScreenHeight() - 110.0 };
}

void bike :: draw()
{
    float rotation = 0;

    if(IsKeyDown(KEY_LEFT))
    {
        rotation = -9;
    }

    if(IsKeyDown(KEY_RIGHT))
    { 
        rotation = 9;
    }
    
    if(IsKeyDown(KEY_SPACE))
    {
        DrawTextureEx(image, position, rotation, 1.0f, YELLOW);
    }
    else
    {
        DrawTextureEx(image, position, rotation, 1.0f, WHITE);
    }
    
    if(IsKeyDown(KEY_SPACE))
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

Rectangle bike :: GetRect()
{
    return {position.x, position.y, (float)image.width, (float)image.height};
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
    DrawRectangleLines(20, 20, 118, 30, WHITE);

    DrawText(TextFormat("Score: %d", score/10), 30, 27, 15, SKYBLUE);

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

bool Game :: End()
{
    for(int i = 0; i < carList.size(); i++)
    {
        if(CheckCollisionRecs(b1.GetRect(), carList[i].GetRect()))
        {
            gameEnded = true;
        }
    }
   return gameEnded;
}

void Game :: Reset()
{
    b1.position = {GetScreenWidth() / 2.0, GetScreenHeight() - 110.0 };
    carList.clear();
    carList.push_back(cars(100, -135));
    carList.push_back(cars(175, -320));
    carList.push_back(cars(250, -510));
    carList.push_back(cars(300, -655));
    gameEnded = false;
    score = 0;
    newMapSoundPlayed = false;
}

int main() {
    int screenWidth = 390;
    int screenHeight = 650;
    Vector2 bgpos = {-350,-600};
    InitWindow(screenWidth, screenHeight, "SpeedRush 2D");
    Texture2D background1 = LoadTexture("graphics/road-1.png");
    Texture2D background2 = LoadTexture("graphics/desert.png");
    Texture2D background = background1;

    InitAudioDevice();  
    Sound Bike = LoadSound("sounds/race.wav");
    Sound GameOver = LoadSound("sounds/game_over.wav");
    Sound NewMap = LoadSound("sounds/new-map.wav");
    Sound buttonPressed = LoadSound("sounds/beep.wav");
    Texture2D menuPage = LoadTexture("graphics/menu_page.png");
    Texture2D gameOver = LoadTexture("graphics/game_over.png");
    
    enum GameState { MENU, PLAYING, GAME_OVER };
    GameState currentState = MENU;
    
    Game game;
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        
        if (currentState == MENU) {
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
        }

        else if (currentState == PLAYING) 
        {   
            game.score++;

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
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (currentState == MENU) 
        {
            ClearBackground(WHITE);
            DrawTexture(menuPage, 0, 10, WHITE);
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

            if(!backgroundChanged && game.score/10 < 150)
             {
                DrawText("Reach 150 to unlock Desert", 25, 60, 11, ORANGE);
            }

            else if(backgroundChanged)
            {
                DrawText("DESERT UNLOCKED!", 24, 60, 12, ORANGE);
            }

            if(IsKeyDown(KEY_SPACE))
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
             DrawRectangle(GetScreenWidth()/2 - 90, 65, 180, 3, GOLD);
             DrawRectangle(GetScreenWidth()/2 - 90, 95, 180, 3, GOLD);
            
             DrawCircle(GetScreenWidth()/2 - 95, 80, 5, GOLD);
             DrawCircle(GetScreenWidth()/2 + 95, 80, 5, GOLD);
             DrawText(TextFormat("Score: %d", game.score/10), 
             GetScreenWidth()/2 - 52, 72, 20, SKYBLUE);
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