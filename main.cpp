#include "game.h" 

using std :: vector, std :: string;

bool backgroundChanged = false;
bool isPaused = false;
bool isMusicPaused = false;

int main() {
    int screenWidth = 390;
    int screenHeight = 650;
    Vector2 bgpos = {-350,-600};
    InitWindow(screenWidth, screenHeight, "SpeedRush 2D");

    Texture2D background1 = LoadTexture("graphics/road-1.png");
    Texture2D background2 = LoadTexture("graphics/desert.png");
    Texture2D menuPage = LoadTexture("graphics/menu-2.png");

    Texture2D gameOver = LoadTexture("graphics/game_over.png");
    Texture2D background = background1;

    InitAudioDevice();  
    Music BackgroundMusic = LoadMusicStream("sounds/background_music.ogg");
    SetMusicVolume(BackgroundMusic, 0.3f);
    Sound Bike = LoadSound("sounds/race.wav");
    SetSoundVolume(Bike, 0.5f);
    Sound GameOver = LoadSound("sounds/game_over.wav");
    SetSoundVolume(GameOver, 0.5f);
    Sound NewMap = LoadSound("sounds/new-map.wav");
    Sound buttonPressed = LoadSound("sounds/beep.wav");
    
    GameState currentState = MENU;
    
    Game game;
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) 
    {
        if (!IsMusicStreamPlaying(BackgroundMusic) && !isMusicPaused)
            {
                PlayMusicStream(BackgroundMusic);
            }
            UpdateMusicStream(BackgroundMusic);

        if(IsKeyPressed(KEY_M))
        {
           PauseMusicStream(BackgroundMusic);
           isMusicPaused = !isMusicPaused;
        }

        if (IsKeyPressed(KEY_P)) 
        {
            isPaused = !isPaused;
            PlaySound(buttonPressed);  

            if (isPaused) 
            {
                PauseSound(Bike); 
            } 
            else 
            {
                ResumeSound(Bike); 
            }
        }
            if (currentState == MENU) 
            {

                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) 
                {
                    PlaySound(buttonPressed);
                    currentState = PLAYING;
                    game.Reset();
                    PlaySound(Bike);
                }

                if (IsKeyPressed(KEY_E)) 
                {
                    break;
                }

                if(IsKeyPressed(KEY_S))
                {
                    PlaySound(buttonPressed);
                    currentState = SHOP;
                }
            }
        
        else if (currentState == SHOP)
        {
            if(game.shop.HandleInput(game.selectedBike, buttonPressed))
            {
            game.b1.SetBike(game.selectedBike);
            }
        }

        else if (currentState == PLAYING) 
    {

        PauseMusicStream(BackgroundMusic);

        if (!isPaused)
        {
            if(IsKeyDown(KEY_SPACE))
            {
                game.score+=2;
            }
            else
            {
                game.score++;
            }

            if(IsKeyDown(KEY_SPACE))
            {
                bgpos.y += 9;  
            }
            else
            {
                bgpos.y += 5;
            }

            if(bgpos.y > GetScreenHeight() - 600)
            {
                bgpos.y = -600;
            }

            game.InputHandling();
            game.update();

            if (!IsSoundPlaying(Bike))
            {
                PlaySound(Bike);  
            }

            if(game.End()) 
            {
                currentState = GAME_OVER;
                PlaySound(GameOver);
                StopSound(Bike);
            }
        }
    }

        else if (currentState == GAME_OVER) 
        {
            if (IsKeyPressed(KEY_Y)) 
            {
                PlaySound(buttonPressed);
                currentState = MENU;
                game.Reset();
                background = background1;
                backgroundChanged = false;
            }

            if(IsKeyPressed(KEY_N))
            {
                break;
            }

            if (IsKeyPressed(KEY_ESCAPE)) 
            {
                break;
            }
        }

        else if(currentState == EXIT)
        {
            break;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (currentState == MENU) 
        {
            DrawTextureEx(menuPage, {0,0}, 0, 1.0f, WHITE);
            const char* titleText = "SpeedRush 2D";
           const char* playText = "Press To Start";
           const char* shopText = "Press To Shop";
           const char* instructionsText = "Instructions";
           const char* exitText = "Press To Exit";

            int titleFontSize = 45;
			int titleWidth = MeasureText(titleText, titleFontSize);
			int titleX = 45;
			int titleY = 40;
			DrawText(titleText, titleX, titleY, titleFontSize, GOLD);
			DrawLine(titleX, titleY + 55, titleWidth, titleY + 55, LIGHTGRAY);

           int TextX = 112;

           // start button 
           game.DrawButton(playText, TextX, 180, 20, buttonPressed, GetMousePosition(), currentState, PLAYING);

           // shop button
           game.DrawButton(shopText, TextX, 280, 20, buttonPressed, GetMousePosition(), currentState, SHOP);

           // instructions button
           game.DrawButton(instructionsText, TextX, 380, 20, buttonPressed, GetMousePosition(), currentState, INSTRUCTIONS);

           // exit button
            game.DrawButton(exitText, TextX, 480, 20, buttonPressed, GetMousePosition(), currentState, EXIT);
        }

        else if(currentState == INSTRUCTIONS)
        {
            DrawTextureEx(menuPage, {0,0}, 0, 1.0f, WHITE);
            DrawRectangle(0, 0, GetScreenWidth() , GetScreenHeight(), Fade(BLACK, 0.3f));
            DrawText("INSTRUCTIONS", 90, 50, 30, GOLD);
            DrawText("Use LEFT and RIGHT arrow keys to move the bike.", 10, 120, 15, LIGHTGRAY);
            DrawText("Press SPACE to boost your speed.", 10, 160, 15, LIGHTGRAY);
            DrawText("Avoid the cars on the road.", 10, 200, 15, LIGHTGRAY);
            DrawText("Reach a score of 150 to unlock the desert \n background.", 10, 240, 15, LIGHTGRAY);
            DrawText("Press P to pause the game.", 10, 290, 15, LIGHTGRAY);

            game.DrawButton("Back to Menu", 150, 550, 15, buttonPressed, GetMousePosition(), currentState, MENU);
        }
        
        else if (currentState == SHOP)
        {
            ClearBackground(RAYWHITE);
            game.shop.Draw(game.selectedBike);
            game.DrawButton("Back to Menu", 150, 570, 15, buttonPressed, GetMousePosition(), currentState, MENU);
        }

        else if (currentState == PLAYING) 
        {
            if(game.score > 150*10 && !backgroundChanged)
            {
                background = background2;
                backgroundChanged = true;

                if(!game.newMapSoundPlayed)
                {
                    PlaySound(NewMap);
                    game.newMapSoundPlayed = true;
                }
            }

            DrawTexture(background, -350, bgpos.y, WHITE);
            DrawTexture(background, -350, bgpos.y - GetScreenHeight(), WHITE);
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.25f));

            if (isPaused)
            {
                DrawText("PAUSED", GetScreenWidth()/2 - 50, GetScreenHeight()/2 - 10, 30, WHITE);
            }

            if(!backgroundChanged && game.score/10 < 150)
            {
                DrawText("Reach 150 to unlock Desert", 25, 60, 11, ORANGE);
            }

            else if(backgroundChanged)
            {
                DrawText("DESERT UNLOCKED!", 24, 60, 12, ORANGE);
            }

            DrawText("Press P to pause", 25, 80, 11, LIGHTGRAY);

            if(IsKeyDown(KEY_SPACE) && !isPaused)
            {
                DrawText("boost active", 158, GetScreenHeight() - 40, 14, RED);
            }

            else
            {
                DrawText("space to boost", 150, GetScreenHeight() - 40, 14, SKYBLUE);
            }

            game.Draw();
        }

        else if (currentState == GAME_OVER) 
        {
             ClearBackground(WHITE);
             DrawTexture(gameOver, 0, 0, WHITE);
             DrawRectangle(GetScreenWidth()/2 - 90, 10, 180, 3, GOLD);
             DrawRectangle(GetScreenWidth()/2 - 90, 40, 180, 3, GOLD);
            
             DrawCircle(GetScreenWidth()/2 - 95, 26, 5, GOLD);
             DrawCircle(GetScreenWidth()/2 + 95, 26, 5, GOLD);
             DrawText(TextFormat("Score: %d", game.score/10), 
             GetScreenWidth()/2 - 52, 16, 20, SKYBLUE);

             DrawText(TextFormat("High Score: %d", game.ScoreManager.getHighScore()), 
                      10, 100, 18, GOLD);

             if(game.IsNewHighScore)
             {
                 DrawText("NEW HIGH SCORE!", 10, 70, 16, RED);
             }
        }
        
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(background1);
    UnloadTexture(background2);
    UnloadSound(Bike);
    UnloadSound(GameOver);
    UnloadSound(NewMap);
    UnloadSound(buttonPressed);
    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}