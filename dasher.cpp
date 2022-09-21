#include "raylib.h"

struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main() {

  // create window dimension values
  const int windowWidth{750};
  const int windowHeight{500};

  // draw the window
  InitWindow(windowWidth, windowHeight, "Dapper Dasher");

  // acceleration due to gravity - pixels per second per second
  const int gravity{1'000};

  // setting up scarfy
  Texture2D scarfy = LoadTexture("textures/scarfy.png");

  // AnimData for scarfy
  // initalized each variable using dot notation
  AnimData scarfyData;
  scarfyData.rec.width = scarfy.width/6;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;
  scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
  scarfyData.pos.y = windowHeight - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.updateTime = (1.0/12.0);
  scarfyData.runningTime = 0.0;

  // setting up nebula
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

  // AnimData for nebula
  // initalized each variable using inline initilization with curly braces
  AnimData nebulaData{ 
    {0.0, 0.0, nebula.width/8, nebula.height/8}, // rectangle rec
    {windowWidth, windowHeight-nebula.height/8}, // vector2 pos
    0, // int frame
    1.0/12.0, // float updateTime
    0.0 // float runningTime
  };

  // AnimaData for nebula2
  AnimData nebula2Data {
    {0.0, 0.0, nebula.width/8, nebula.height/8}, // rectangle rec
    {windowWidth, windowHeight - (2 * nebula.height/8)}, // vector2 pos
    0, // int frame
    1.0/16.0, // float updateTime
    0.0 // float runningTime
  };

  // integer for nebula X velocity (pixels per second)
  // because the nebula is moving right to left it has to move using a NEGATIVE value
  int nebulaVel{-200};
  int nebula2Vel{-100};

  // jump velocity pixels per second
  int jump_vel{-600};

  // variable for is in air check
  bool isInAir{};

  // dimensions for rectangle
  int rectangle_velocity{0};

  // initalize FPS value
  int FPS{60};

  // set FPS value
  SetTargetFPS(FPS);

  // these are the previous variables used before moving to the struct method and creating AnimData structs
  // Rectangle scarfyRec;
  // scarfyRec.width = scarfy.width/6;
  // scarfyRec.height = scarfy.height;
  // scarfyRec.x = 0;
  // scarfyRec.y = 0;
  // Vector2 scarfyPos;
  // scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
  // scarfyPos.y = windowHeight - scarfyRec.height;

   // You can use brace initalization to initalize each value on the same line as the object definition
  // above, I used the regular multi-line initialization for scarfy
  // Rectangle nebulaRec{0.0, 0.0, nebula.width/8.0, nebula.height/8.0};
  // Vector2 nebulaPos{windowWidth, windowHeight-nebulaRec.height};

  // variable for other instances of nebulas
  // Rectangle nebula2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
  // Vector2 nebula2Pos{windowWidth, windowHeight - (2 * nebulaRec.height)};
  // int nebula2Frame{};
  // const float nebula2UpdateTime{1.0/16.0};
  // float nebula2RunningTime{};
  // animation frame for the nebula
  // int nebulaFrame{};
  // update time float - the amount of time that passes between each animation frame
  // const float nebulaUpdateTime{1.0/12.0};
  // float nebulaRunningTime{};
  // animation frame for scarfy
  // int frame{};
  // update time float - the amount of time that passes between each animation frame
  // const float updateTime{1.0 / 12.0};
  // float runningTime{};

  while (!WindowShouldClose()) 
  {

    BeginDrawing();

    ClearBackground(RAYWHITE);

    // draw nebula
    DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);

    // delta time (time since last frame)
    const float dT{GetFrameTime()};
    
    // make the nebula move across the screen
    nebulaData.pos.x += nebulaVel * dT;

    // update nebula running time
    nebulaData.runningTime += dT;

    // check to see if runtime is greater than last frame update
    if (nebulaData.runningTime >= nebulaData.updateTime){
      // reset nebula running time
      nebulaData.runningTime = 0.0;

      // update animation frame
      nebulaData.rec.x = nebulaData.frame * nebulaData.rec.width;
      nebulaData.frame++;
      if (nebulaData.frame > 7){
        // reset frame back to 0 if it's exceded 8
        nebulaData.frame = 0;
      }
    }

    // move the second nebula across the screen
    nebula2Data.pos.x += nebula2Vel * dT;
    nebula2Data.runningTime += dT;

    // draw and animate the second nebula
    DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos, GREEN);
    if (nebula2Data.runningTime >= nebula2Data.updateTime){
      nebula2Data.runningTime = 0.0;
      nebula2Data.rec.x = nebula2Data.frame * nebula2Data.rec.width;
      nebula2Data.frame++;
      if (nebula2Data.frame > 7){
        nebula2Data.frame = 0;
      }
    }

    // draw Scarfy
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE); 

    // update running time
    scarfyData.runningTime += dT;

    if (scarfyData.runningTime >= scarfyData.updateTime){
      // reset running time
      scarfyData.runningTime = 0.0;

      // update animation frame
      if (isInAir == false){
        scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
        scarfyData.frame++;
        if (scarfyData.frame > 5){
          scarfyData.frame = 0;
        }
      }
    }

    // check if scarfy is on ground
    if (scarfyData.pos.y >= windowHeight - scarfyData.rec.width){  
      // scarfy is on graound
      rectangle_velocity = 0;
      isInAir = false;
    } else {
      // scarfy is in air - apply gravity
      rectangle_velocity += gravity * dT;
      isInAir = true;
    }

    // check for jumping
    if (IsKeyPressed(KEY_SPACE) && isInAir == false){
      rectangle_velocity += jump_vel;
    }

    // update position
    scarfyData.pos.y += rectangle_velocity * dT;

    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();

}