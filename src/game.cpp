#include "game.h"

// game functions definitions
Game :: Game()
{
    carList.push_back(cars(100, -135));
    carList.push_back(cars(175, -320));
    carList.push_back(cars(250, -510));
    carList.push_back(cars(300, -655));
}

void Game :: update()
{
    for(int i=0; i < carList.size(); i++)
    {
       carList[i].Update();
    }
}

void Game :: Draw()
{
    b1.draw();

    for(int i=0; i < carList.size(); i++)
    {
        carList[i].draw();
    } 

    DrawRectangle(20, 20, 118, 30, BLACK);
    DrawRectangleLines(20, 20, 118, 30, SKYBLUE);
    DrawText(TextFormat("Score: %d", score/10), 30, 27, 15, SKYBLUE);
    
    string bikeText;
    
    if(selectedBike == SCOOTY)
    {
        bikeText = "Scooty";
    }
    else
    {
        bikeText = "Ninja H2R";
    }
    DrawRectangle(260, 24, 118, 30, BLACK);
    DrawRectangleLines(260, 24, 118, 30, GREEN);
    DrawText(bikeText.c_str(), 300, 32, 13, GREEN);
}

void Game :: InputHandling()
{
    if(IsKeyDown(KEY_RIGHT))
    {
        b1.MoveRight();
    }
    else if(IsKeyDown(KEY_LEFT))
    {
        b1.MoveLeft();
    }
}


bool Game :: DrawButton(const char* text, int x, int y, int fontSize, Sound buttonSound, Vector2 mousePos, GameState &currentState, GameState targetState)
{
    int width = MeasureText(text, fontSize);
    Rectangle buttonRect = { x - 10, y - 10, width + 20, fontSize + 20 };

    // Hover effect
    Color buttonColor;
	if(CheckCollisionPointRec(mousePos, buttonRect))
	{
		buttonColor = ORANGE;
	}
	else
	{
		buttonColor = RED;
	}

    DrawRectangle(x - 10, y - 10, width + 20, fontSize + 20, buttonColor);
    DrawText(text, x, y, fontSize, WHITE);

    // check collison
    if (CheckCollisionPointRec(mousePos, buttonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        PlaySound(buttonSound);
        currentState = targetState;
        return true;
    }

    return false;
}


bool Game :: End()
{
    for(int i = 0; i < carList.size(); i++)
    {
        if(CheckCollisionRecs(b1.GetRect(), carList[i].GetRect()))
        {
            gameEnded = true;
            int finalScore = score / 10;
            IsNewHighScore = ScoreManager.IsNewHighScore(finalScore);
            ScoreManager.CheckScore(finalScore);
        }
    }
   return gameEnded;
}

void Game :: Reset()
{
    b1.position = {(float)(GetScreenWidth() / 2.0), (float)(GetScreenHeight() - 110.0)};
    b1.SetBike(selectedBike); 
    carList.clear();
    carList.push_back(cars(100, -135));
    carList.push_back(cars(175, -320));
    carList.push_back(cars(250, -510));
    carList.push_back(cars(300, -655));
    gameEnded = false;
    score = 0;
    newMapSoundPlayed = false;
    IsNewHighScore = false;
}
