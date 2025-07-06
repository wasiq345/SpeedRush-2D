#include <iostream>
#include<fstream>

using namespace std;

class HighScore
{
    int highScore;
    string FileName;
public:
    HighScore()
    {
        FileName = "HighScore.txt";
        LoadScore();
    }
    
    void LoadScore()
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

    void SaveScore()
    {
        ofstream file(FileName);
        if(file.is_open())
        {
            file << highScore;
            file.close();
        }
    }

    void CheckScore(int NewScore)
    {
        LoadScore();
        if(NewScore > highScore)
        {
            highScore = NewScore;
            SaveScore();
        }
    }

    int getHighScore()
    {
        return highScore;
    }

    bool IsNewHighScore(int score)
    {
        return score > highScore;
    }
};
