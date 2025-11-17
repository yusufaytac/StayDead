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
    int MedicVel = 140;
    int Medic2Vel = 220;
    int Medic3Vel = 190;
    int Medic4Vel = 170;

    const float ZombiePaddingX = 39.0f;  
    const float ZombiePaddingY = 57.0f;  
    const float ZombieRealWidth = 50.0f; 
    const float ZombieRealHeight = 70.0f;

    Color MyColor = { 20, 30, 50, 255 };

    // initialize window
    InitWindow(WindowDimension[0], WindowDimension[1], "Stay Dead!");

    Texture2D City = LoadTexture("textures/city-update.png");

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

    // health bar texture
    Texture2D Bar = LoadTexture("textures/healthbar.png");
    
    const int SizeOfMedic = 1;
    const int SizeOfPoison = 10;
    
    // medical kit texture
    Texture2D Medic = LoadTexture("textures/medicalkit-update.png");
    AnimData MedicData{
        {0, 0, Medic.width, Medic.height},
        {0, 0},
        0,
        0,
        0     
    };
    // medic 1
    AnimData Medic1[SizeOfMedic]{MedicData};
    for (int i = 0; i<SizeOfMedic; i++)
    {   
        Medic1[i].Pos.x = MedicData.Pos.x +40;
        Medic1[i].Pos.y = -(i * 600);

    }
    // medic 2
    AnimData Medic2[SizeOfMedic]{MedicData};
    for (int i = 0; i<SizeOfMedic; i++)
    {
        Medic2[i].Pos.x = MedicData.Pos.x + 120;
        Medic2[i].Pos.y = -(i * 750);
    }

    // medic 3
    AnimData Medic3[SizeOfMedic]{MedicData};
    for (int i = 0; i<SizeOfMedic; i++)
    {
        Medic3[i].Pos.x = MedicData.Pos.x + 230;
        Medic3[i].Pos.y = -(i * 900);
    }
    // medic 4
    AnimData Medic4[SizeOfMedic]{MedicData};
    for (int i = 0; i<SizeOfMedic; i++)
    {
        Medic4[i].Pos.x = MedicData.Pos.x + 320;
        Medic4[i].Pos.y = -(i * 1100);
    }




   
    int Health = 0;
    bool GameOver = false;

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        
       BeginDrawing();
       ClearBackground(BLACK);
       DrawTexture(City, 0, 0, WHITE);
       
       // delta time 
       const float DeltaTime = GetFrameTime();
       bool IsWalking = false;
       
       
       // character collision
       Rectangle PlayerCollisionBox;
       PlayerCollisionBox.x = ZombieWalkData.Pos.x + ZombiePaddingX;
       PlayerCollisionBox.y = ZombieWalkData.Pos.y + ZombiePaddingY;
       PlayerCollisionBox.width = ZombieRealWidth;
       PlayerCollisionBox.height = ZombieRealHeight;


       if(!GameOver)
       { 
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
            if (Medic1[i].Pos.y > WindowDimension[1])
            {
                Medic1[i].Pos.y = -150; // return
            }
            DrawTexture(Medic, Medic1[i].Pos.x, Medic1[i].Pos.y, WHITE);
            // medic1 collision
            Rectangle MedicBox = {Medic1[i].Pos.x, Medic1[i].Pos.y, Medic.width, Medic.height};
            if(CheckCollisionRecs(PlayerCollisionBox, MedicBox))
            {   
                Medic1[i].Pos.y = -150; // return
                Health = Health + 1;
            }
       }
       // update medic2
       for (int i = 0; i<SizeOfMedic; i++)
       {
            Medic2[i].Pos.y = Medic2[i].Pos.y + Medic2Vel * DeltaTime;
            if (Medic2[i].Pos.y > WindowDimension[1])
            {
                Medic2[i].Pos.y = -150; // return
            }
            DrawTexture(Medic, Medic2[i].Pos.x, Medic2[i].Pos.y, WHITE);
            // medic2 collision
            Rectangle MedicBox = {Medic2[i].Pos.x, Medic2[i].Pos.y, Medic.width, Medic.height};
            if(CheckCollisionRecs(PlayerCollisionBox, MedicBox))
            {   
                Medic2[i].Pos.y = -150; // return
                Health = Health + 1;
            }
       }
       // update medic3
       for (int i = 0; i<SizeOfMedic; i++)
       {
            Medic3[i].Pos.y = Medic3[i].Pos.y + Medic3Vel * DeltaTime;
            if (Medic3[i].Pos.y > WindowDimension[1])
            {
                Medic3[i].Pos.y = -150; // return
            }
            DrawTexture(Medic, Medic3[i].Pos.x, Medic3[i].Pos.y, WHITE);
            // medic3 collision
            Rectangle MedicBox = {Medic3[i].Pos.x, Medic3[i].Pos.y, Medic.width, Medic.height};
            if(CheckCollisionRecs(PlayerCollisionBox, MedicBox))
            {   
                Medic3[i].Pos.y = -150; // return
                Health = Health + 1;
            }
       }
       // update medic4
       for (int i = 0; i<SizeOfMedic; i++)
       {
            Medic4[i].Pos.y = Medic4[i].Pos.y + Medic4Vel * DeltaTime;
            if (Medic4[i].Pos.y > WindowDimension[1])
            {
                Medic4[i].Pos.y = -150; // return
            }
            DrawTexture(Medic, Medic4[i].Pos.x, Medic4[i].Pos.y, WHITE);
            // medic4 collision
            Rectangle MedicBox = {Medic4[i].Pos.x, Medic4[i].Pos.y, Medic.width, Medic.height};
            if(CheckCollisionRecs(PlayerCollisionBox, MedicBox))
            {   
                Medic4[i].Pos.y = -150; // return
                Health = Health + 1;
            }
       }
       if(Health == 3)
       {
            GameOver = true;
       }

       }
       else
       {
            DrawText("GAME OVER!", WindowDimension[0]/2-60, WindowDimension[1]/2+20, 20, WHITE);
       }

       
       

       
      

       EndDrawing();
    }

    UnloadTexture(Medic);
    UnloadTexture(ZombieIdle);
    UnloadTexture(ZombieWalk);
    
    CloseWindow();
}