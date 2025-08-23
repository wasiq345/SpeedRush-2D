#include "HighScore.h"

using namespace std;

HighScore :: HighScore()
    {
        FileName = "HighScore.txt";
        LoadScore();
    }
    
void HighScore :: LoadScore()
    {
        ifstream file(FileName);
        if(file.is_open())
        {
            file >> highScore;
            file.close();
        }
        else
        {
            highScore = 0;
        }
    }

void HighScore :: SaveScore()
    {
        ofstream file(FileName);
        if(file.is_open())
        {
            file << highScore;
            file.close();
        }
    }

void HighScore :: CheckScore(int NewScore)
    {
        LoadScore();
        if(NewScore > highScore)
        {
            highScore = NewScore;
            SaveScore();
        }
    }

int HighScore :: getHighScore()
    {
        return highScore;
    }

bool HighScore :: IsNewHighScore(int score)
    {
        return score > highScore;
    }

