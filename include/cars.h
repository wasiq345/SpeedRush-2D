#pragma once
#include "vehicle.h"

class cars : public Vehicle
{
public: 
    void draw() override;
    void Update() override;
    cars(float StartX, float StartY);
    Rectangle GetRect() override;
};