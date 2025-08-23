#pragma once

#include <raylib.h>
#include "gametypes.h"

class Shop 
{
private:
    Texture2D shopMenu;
    Texture2D scootyImage;
    Texture2D ninjaImage;
    
    Rectangle leftArrowRect;
    Rectangle rightArrowRect;
    Rectangle selectButtonRect;
    
    int currentBikeIndex;
    BikeType bikes[2] = {SCOOTY, NINJA_H2R};
    const char* bikeNames[2] = {"Scooty", "Ninja H2R"};
    const char* bikeStats[2] = {"Agility : High \n Speed : 5", "Agility : Medium \n Speed : 7" };
    
public:
    Shop();
    ~Shop(); // Destructor to unload textures
    void Draw(BikeType selectedBike);
    bool HandleInput(BikeType& currentBike, Sound buttonSound);
    bool HandleMouseInput(BikeType& currentBike, Sound buttonSound);
    void NextBike();
    void PreviousBike();
    BikeType GetCurrentDisplayBike();
};

