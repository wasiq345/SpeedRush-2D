#pragma once

#include <fstream>
#include <iostream>

class HighScore {
    int highScore;
    std::string FileName;
public:
    HighScore();
    void LoadScore();
    void SaveScore();
    void CheckScore(int NewScore);
    int getHighScore();
    bool IsNewHighScore(int score);
};