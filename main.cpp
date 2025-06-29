#include <raylib.h>
#include <iostream>
#include<vector>
using namespace std;


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
        int RandomIndex = GetRandomValue(30, GetScreenWidth() - 50);
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
    image = LoadTexture("graphics/bike-1.png");
    speed = 5;
    position = {GetScreenWidth() / 2.0, GetScreenHeight() - 110.0 };
}

void bike :: draw()
{
    DrawTexture(image, position.x, position.y, WHITE);
    if(IsKeyDown(KEY_SPACE))
    {
        image = LoadTexture("graphics/bike-2.png");
    }
    else
    {
        image = LoadTexture("graphics/bike-1.png");

    }
}

void bike :: Update()
{
    
}

void bike :: MoveLeft()
{
    if(position.x > 30)
    {
      position.x -= speed;
    }
}

void bike :: MoveRight()
{
    if(position.x < GetScreenWidth() - image.width - 30)
    {
      position.x += speed;
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
}

int main() {
    int screenWidth = 390;
    int screenHeight = 650;
    Vector2 bgpos = {-350,-600};
    InitWindow(screenWidth, screenHeight, "SpeedRush 2D");
    Texture2D background = LoadTexture("graphics/road.png");
    InitAudioDevice();  
    Sound Bike = LoadSound("sounds/race.wav");
    Sound GameOver = LoadSound("sounds/game_over.wav");
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
                currentState = MENU;
                game.Reset();
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
            DrawTexture(background, -350, bgpos.y, WHITE);
            DrawTexture(background, -350, bgpos.y - GetScreenHeight(), WHITE);
            DrawText("space to boost", 150, GetScreenHeight() - 40, 14, SKYBLUE);
            game.Draw();
        }
        else if (currentState == GAME_OVER) 
        {
             ClearBackground(WHITE);
             DrawTexture(gameOver, 0, 0, WHITE);
        }
        
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadSound(Bike);
    UnloadSound(GameOver);
    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}