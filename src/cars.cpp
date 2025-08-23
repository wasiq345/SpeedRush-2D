#include "cars.h"

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