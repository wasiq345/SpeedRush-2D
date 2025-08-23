#pragma once
#include "vehicle.h"

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
