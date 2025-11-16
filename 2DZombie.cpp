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

    const int Velocity = 100;
    int MedicVel = 150;
    int Medic2Vel = 100;

    // initialize window
    InitWindow(WindowDimension[0], WindowDimension[1], "Stay Dead!");

    // zombie idle texture
    Texture2D ZombieIdle = LoadTexture("textures/Idle3.png");
    AnimData ZombieIdleData{
            {0, 0, ZombieIdle.width/7, ZombieIdle.height}, // rectangle rec
            {WindowDimension[0]/2 - ZombieIdleData.Rec.width/2, WindowDimension[1] - ZombieIdleData.Rec.height}, // vector2 pos
            0, // int frame
            1.0/12.0, // float update time
            0 // float move time
    };

    // zombie walk texture
    Texture2D ZombieWalk = LoadTexture("textures/Walk3.png");
    const float FrameWidth = ZombieWalk.width/12;
    AnimData ZombieWalkData{
            {0, 0, FrameWidth, ZombieWalk.height}, // rectangle rec
            {WindowDimension[0]/2 - ZombieWalkData.Rec.width/2, WindowDimension[1] - ZombieWalkData.Rec.height}, // vector2 pos
            0, // int frame
            1.0/24.0, // float update time
            0.0 // float move time
    };

    
    const int SizeOfMedic = 10;
    // medical kit texture
    Texture2D Medic = LoadTexture("textures/medicalkit.png");
    AnimData MedicData{
        {0, 0, Medic.width, Medic.height},
        {100, 0},
        0,
        0,
        0     
    };
    // medic 1
    AnimData Medic1[SizeOfMedic]{MedicData};
    for (int i = 0; i<SizeOfMedic; i++)
    {   
        Medic1[i].Pos.x = MedicData.Pos.x;
        Medic1[i].Pos.y = -(i * 600);
    }

    // medic 2
    AnimData Medic2[SizeOfMedic]{MedicData};
    for (int i = 0; i<SizeOfMedic; i++)
    {
        Medic2[i].Pos.x = MedicData.Pos.x +50;
        Medic2[i].Pos.y = -(i * 600);
    }


    
    

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        
       BeginDrawing();
       ClearBackground(WHITE);
    

       // delta time 
       const float DeltaTime = GetFrameTime();
       bool IsWalking = false;

       // ıdle animation
       if(!IsWalking)
       {
        ZombieIdleData.Pos.x = ZombieWalkData.Pos.x; 
        ZombieIdleData.MoveTime = ZombieIdleData.MoveTime + DeltaTime;
        if(ZombieIdleData.MoveTime >= ZombieIdleData.UpdateTime)
        {
            ZombieIdleData.MoveTime = 0.0;
            ZombieIdleData.Rec.x = ZombieIdleData.Frame * ZombieIdleData.Rec.width;
            ZombieIdleData.Frame = ZombieIdleData.Frame + 1;
            if(ZombieIdleData.Frame >6)
            {
                ZombieIdleData.Frame = 0;
            }
        }
        
       }
       
       // walk animation
       if(IsKeyDown(KEY_D))
       {    
            IsWalking = true;
            ZombieWalkData.Rec.width = FrameWidth;
            ZombieWalkData.Pos.x = ZombieWalkData.Pos.x + (Velocity * DeltaTime);
            ZombieWalkData.MoveTime = ZombieWalkData.MoveTime + DeltaTime;
            if(ZombieWalkData.MoveTime >= ZombieWalkData.UpdateTime && IsWalking == true)
            {
                ZombieWalkData.MoveTime = 0;
                ZombieWalkData.Rec.x = ZombieWalkData.Frame * ZombieWalkData.Rec.width;
                ZombieWalkData.Frame = ZombieWalkData.Frame + 1;
                if(ZombieWalkData.Frame > 11)
                {
                    ZombieWalkData.Frame = 0;
                }

            }
            
       }

       if(IsKeyDown(KEY_A))
       {    
            IsWalking = true;
            ZombieWalkData.Rec.width = -FrameWidth;
            ZombieWalkData.Pos.x = ZombieWalkData.Pos.x + (-Velocity * DeltaTime);
            ZombieWalkData.MoveTime = ZombieWalkData.MoveTime + DeltaTime;
            if(ZombieWalkData.MoveTime >= ZombieWalkData.UpdateTime && IsWalking == true)
            {   
                
                ZombieWalkData.MoveTime = 0;
                ZombieWalkData.Rec.x = ZombieWalkData.Frame * ZombieWalkData.Rec.width;
                ZombieWalkData.Frame = ZombieWalkData.Frame - 1;
                if(ZombieWalkData.Frame > 11)
                {
                    ZombieWalkData.Frame = 0;
                }

            }
            
       }



       if(!IsWalking)
       {
            DrawTextureRec(ZombieIdle, ZombieIdleData.Rec, ZombieIdleData.Pos, WHITE);
       }
       else
       {
            DrawTextureRec(ZombieWalk, ZombieWalkData.Rec, ZombieWalkData.Pos, WHITE);
       }

       // update medic1
       for (int i = 0; i<SizeOfMedic; i++)
       {
            // update the position of each medic
            Medic1[i].Pos.y = Medic1[i].Pos.y + MedicVel * DeltaTime;
            DrawTexture(Medic, Medic1[i].Pos.x, Medic1[i].Pos.y, WHITE);
       }
       // update medic2
       for (int i = 0; i<SizeOfMedic; i++)
       {
            Medic2[i].Pos.y = Medic2[i].Pos.y + Medic2Vel * DeltaTime;
            DrawTexture(Medic, Medic2[i].Pos.x, Medic2[i].Pos.y, WHITE);
       }



       
      

       EndDrawing();
    }
    UnloadTexture(Medic);
    UnloadTexture(ZombieIdle);
    UnloadTexture(ZombieWalk);
    
    CloseWindow();
}