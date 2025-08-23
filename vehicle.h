#pragma once

#include <raylib.h>
#include "gametypes.h"

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
