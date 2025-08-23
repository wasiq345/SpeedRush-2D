#include "shop.h"

// Shop implementation
Shop::Shop()
{
    shopMenu = LoadTexture("graphics/menu-2.png");
    scootyImage = LoadTexture("graphics/scooty.png");
    ninjaImage = LoadTexture("graphics/bike.png");
    
    currentBikeIndex = 0;
    
    // Define button positions
    leftArrowRect = {50, 300, 60, 40};
    rightArrowRect = {280, 300, 60, 40};
    selectButtonRect = {260, 480, 90, 27};
}

void Shop::Draw(BikeType selectedBike)
{
    DrawTexture(shopMenu, 0, 0, WHITE);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.3f));
    
    // Title
    DrawText("BIKE SELECTION", 90, 80, 25, GOLD);
    DrawLine(90, 110, 300, 110, GOLD);
    
    // Bike display area background
    DrawRectangle(70, 150, 250, 190, Fade(DARKGRAY, 0.8f));
    DrawRectangleLines(70, 150, 250, 190, WHITE);
    
     // Current bike image (centered)
    Texture2D currentBikeTexture;
    if (bikes[currentBikeIndex] == SCOOTY) {
        currentBikeTexture = scootyImage;
    } else {
        currentBikeTexture = ninjaImage;
    }
    
    // // Center the bike image
    int bikeX = 185 - currentBikeTexture.width / 2;
    int bikeY = 200;
    DrawTextureEx(currentBikeTexture, {(float)bikeX, (float)bikeY}, 0, 2.0f, WHITE);
    
    // Left Arrow Button
    Vector2 mousePos = GetMousePosition();
    Color leftColor = CheckCollisionPointRec(mousePos, leftArrowRect) ? ORANGE : DARKGRAY;
    DrawRectangleRec(leftArrowRect, leftColor);
    DrawRectangleLinesEx(leftArrowRect, 2, WHITE);
    DrawText("<", leftArrowRect.x + 25, leftArrowRect.y + 10, 20, WHITE);
    
    // Right Arrow Button  
    Color rightColor = CheckCollisionPointRec(mousePos, rightArrowRect) ? ORANGE : DARKGRAY;
    DrawRectangleRec(rightArrowRect, rightColor);
    DrawRectangleLinesEx(rightArrowRect, 2, WHITE);
    DrawText(">", rightArrowRect.x + 25, rightArrowRect.y + 10, 20, WHITE);
    
    // Bike info
    DrawText(bikeNames[currentBikeIndex], 135, 365, 25, GOLD);
    DrawText(bikeStats[currentBikeIndex], 40, 480, 17, LIGHTGRAY);
    
    // Selection status
    if (selectedBike == bikes[currentBikeIndex]) {
        DrawText("CURRENTLY \n SELECTED", selectButtonRect.x + 20, selectButtonRect.y + 5, 14, GREEN);
    } else {
        // Select button
        Color selectColor = CheckCollisionPointRec(mousePos, selectButtonRect) ? GREEN : DARKGREEN;
        DrawRectangleRec(selectButtonRect, selectColor);
        DrawRectangleLinesEx(selectButtonRect, 2, WHITE);
        DrawText("SELECT", selectButtonRect.x + 20, selectButtonRect.y + 8, 14, WHITE);
    }
    
    // Bike indicator dots
    for(int i = 0; i < 2; i++) {
        Color dotColor = (i == currentBikeIndex) ? GOLD : GRAY;
        DrawCircle(180 + i * 30, 580, 5, dotColor);
    }
}

bool Shop::HandleInput(BikeType& currentBike, Sound buttonSound)
{
    // Keyboard input
    if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        PreviousBike();
        PlaySound(buttonSound);
        return false;
    }
    
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        NextBike();
        PlaySound(buttonSound);
        return false;
    }
    
    if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        currentBike = bikes[currentBikeIndex];
        PlaySound(buttonSound);
        return true; // Bike selected
    }
    
    // Mouse input
    return HandleMouseInput(currentBike, buttonSound);
}

bool Shop::HandleMouseInput(BikeType& currentBike, Sound buttonSound)
{
    Vector2 mousePos = GetMousePosition();
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Left arrow clicked
        if(CheckCollisionPointRec(mousePos, leftArrowRect)) {
            PreviousBike();
            PlaySound(buttonSound);
            return false;
        }
        
        // Right arrow clicked
        if(CheckCollisionPointRec(mousePos, rightArrowRect)) {
            NextBike();
            PlaySound(buttonSound);
            return false;
        }
        
        // Select button clicked (only if not already selected)
        if(CheckCollisionPointRec(mousePos, selectButtonRect) && 
           currentBike != bikes[currentBikeIndex]) {
            currentBike = bikes[currentBikeIndex];
            PlaySound(buttonSound);
            return true;
        }
    }
    
    return false;
}

void Shop::NextBike()
{
    currentBikeIndex = (currentBikeIndex + 1) % 2;
}

void Shop::PreviousBike()
{
    currentBikeIndex = (currentBikeIndex - 1 + 2) % 2;
}

BikeType Shop::GetCurrentDisplayBike()
{
    return bikes[currentBikeIndex];
}

Shop::~Shop()
{
    UnloadTexture(shopMenu);
    UnloadTexture(scootyImage);
    UnloadTexture(ninjaImage);
}

