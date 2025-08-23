#pragma once
#include "HighScore.h"
#include "shop.h"
#include "bike.h"
#include "cars.h"
#include<vector>
using std :: vector, std :: string;


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