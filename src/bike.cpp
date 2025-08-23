#include "bike.h"
// bike definitions
bike :: bike()
{
    normalScooty = LoadTexture("graphics/scooty.png");
    boostScooty = LoadTexture("graphics/boost-scooty.png");
    
    normalNinja = LoadTexture("graphics/bike.png");
    boostNinja = LoadTexture("graphics/boost-bike.png");
    
    currentBike = SCOOTY;
    SetBike(SCOOTY);
    position = {(float)(GetScreenWidth() / 2.0), (float)(GetScreenHeight() - 110.0)};
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