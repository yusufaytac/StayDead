#include "raylib.h"

struct AnimData
{
    Rectangle Rec;
    Vector2 Pos;
    int Frame;
    float UpdateTime;
    float MoveTime;

};

int main()
{
    // window dimensions
    int WindowDimension[2];
    WindowDimension[0] = 380;
    WindowDimension[1] = 512;

    // initialize window
    InitWindow(WindowDimension[0], WindowDimension[1], "Stay Dead!");

    bool IsWalking = false;

    // zombie idle
    Texture2D ZombieIdle = LoadTexture("textures/Idle.png");
    AnimData ZombieIdleData{
            {0, 0, ZombieIdle.width/6, ZombieIdle.height},
            {WindowDimension[0]/2 - ZombieIdleData.Rec.width/2, WindowDimension[1] - ZombieIdleData.Rec.height,}, 
            0, 
            1.0/12.0, 
            0.0
    };

    // zombie walking
    Texture2D ZombieWalk = LoadTexture("texture/Walk.png");
    AnimData ZombieWalkData{
        {0, 0, ZombieWalk.width/6, ZombieWalk.height},
        {}

    };

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        // delta time
        const float DeltaTime = GetFrameTime();

        // ıdle
        ZombieIdleData.MoveTime = ZombieIdleData.MoveTime + DeltaTime;
        if(ZombieIdleData.MoveTime >= ZombieIdleData.UpdateTime && !IsWalking)
        {
            ZombieIdleData.MoveTime = 0.0;
            // update animation fram
            ZombieIdleData.Rec.x = ZombieIdleData.Frame * ZombieIdleData.Rec.width;
            ZombieIdleData.Frame = ZombieIdleData.Frame + 1;
            if(ZombieIdleData.Frame > 5)
            {
                ZombieIdleData.Frame = 0;
            }

        }

        // walking
        

        
        DrawTextureRec(ZombieIdle, ZombieIdleData.Rec, ZombieIdleData.Pos, WHITE);
        
        EndDrawing();
    }
    UnloadTexture(ZombieIdle);
    CloseWindow();
}