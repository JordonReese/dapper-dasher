#include "raylib.h"
#include <stdlib.h> // include for rand();

struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main() {

  // array for windowsize
  int windowDimensions[2];
  windowDimensions[0] = 750;
  windowDimensions[1] = 500;

  // create window dimension values
  // const int windowWidth{750};
  // const int windowHeight{500};

  // draw the window
  InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

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
  scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
  scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.updateTime = (1.0/12.0);
  scarfyData.runningTime = 0.0;

  // setting up nebula
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

  // size of nebulaArray
  int sizeOfNebulaArray{6};
  
  // array of animData
  AnimData nebulaArray[sizeOfNebulaArray]{};

  // for loop
  for (int i = 0; i < sizeOfNebulaArray; i++) {
    nebulaArray[i].rec.x = 0.0;
    nebulaArray[i].rec.y = 0.0;
    nebulaArray[i].rec.width = nebula.width/8;
    nebulaArray[i].rec.height = nebula.height/8;
    nebulaArray[i].pos.x = windowDimensions[0] + i * 300;
    nebulaArray[i].pos.y = windowDimensions[1] - nebula.height/8;
    nebulaArray[i].frame = 0;
    nebulaArray[i].runningTime = 0.0;
  }

  // // integer for nebula X velocity (pixels per second)
  // // because the nebula is moving right to left it has to move using a NEGATIVE value
  int nebulaVel{-200};

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
  // switched to using a for loop to initalize all the values for the animdata 
  // AnimData for nebula
  // initalized each variable using inline initilization with curly braces
  // AnimData nebulaData{ 
  //   {0.0, 0.0, nebula.width/8, nebula.height/8}, // rectangle rec
  //   {windowDimensions[0], windowDimensions[1]-nebula.height/8}, // vector2 pos
  //   0, // int frame
  //   1.0/12.0, // float updateTime
  //   0.0 // float runningTime
  // };
  // // AnimaData for nebula2
  // AnimData nebula2Data {
  //   {0.0, 0.0, nebula.width/8, nebula.height/8}, // rectangle rec
  //   {windowDimensions[0], windowDimensions[1] - (2 * nebula.height/8)}, // vector2 pos
  //   0, // int frame
  //   1.0/16.0, // float updateTime
  //   0.0 // float runningTime
  // };
  // changed to using a for loop for animation update
  // // check to see if runtime is greater than last frame update
  // if (nebulaArray[0].runningTime >= nebulaArray[0].updateTime){
  //   // reset nebula running time
  //   nebulaArray[0].runningTime = 0.0;
  //   // update animation frame
  //   nebulaArray[0].rec.x = nebulaArray[0].frame * nebulaArray[0].rec.width;
  //   nebulaArray[0].frame++;
  //   if (nebulaArray[0].frame > 7){
  //     // reset frame back to 0 if it's exceded 8
  //     nebulaArray[0].frame = 0;
  //   }
  // }
  // if (nebulaArray[1].runningTime >= nebulaArray[1].updateTime){
  //   nebulaArray[1].runningTime = 0.0;
  //   nebulaArray[1].rec.x = nebulaArray[1].frame * nebulaArray[1].rec.width;
  //   nebulaArray[1].frame++;
  //   if (nebulaArray[1].frame > 7){
  //     nebulaArray[1].frame = 0;
  //   }
  // }
  // original way of updating nebula animations
  // // make the nebula move across the screen
  // nebulaArray[0].pos.x += nebulaVel * dT;
  // // update nebula running time
  // nebulaArray[0].runningTime += dT;
  // // move the second nebula across the screen
  // nebulaArray[1].pos.x += nebula2Vel * dT;
  // nebulaArray[1].runningTime += dT;
  // draw and animate the second nebula
  // DrawTextureRec(nebula, nebulaArray[1].rec, nebulaArray[1].pos, GREEN);
  // draw nebula
  // DrawTextureRec(nebula, nebulaArray[0].rec, nebulaArray[0].pos, WHITE);

  while (!WindowShouldClose()) 
  {
    // delta time (time since last frame)
    const float dT{GetFrameTime()};

    BeginDrawing();

    ClearBackground(RAYWHITE);

    // check if scarfy is on ground
    if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.width){  
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

    

    // using a for loop to move nebulas across the screen
    for (int i = 0; i < sizeOfNebulaArray; i++){
      nebulaArray[i].pos.x += nebulaVel * dT;
      nebulaArray[i].runningTime += dT;
    }
    
    // using a for loop to create each nebula
    for (int i = 0; i < sizeOfNebulaArray; i++){
      DrawTextureRec(nebula, nebulaArray[i].rec, nebulaArray[i].pos, WHITE);
    }

    // using a for loop to update the animation for each nebula
    for (int i = 0; i < sizeOfNebulaArray; i++){
      if (nebulaArray[i].runningTime >= nebulaArray[i].updateTime){
        // reset nebula running time
        nebulaArray[i].runningTime = 0.0;
        // update animation frame
        nebulaArray[i].rec.x = nebulaArray[i].frame * nebulaArray[i].rec.width;
        nebulaArray[i].frame++;
        if (nebulaArray[i].frame > 7){
          // reset frame back to 0 if it's exceded 8
          nebulaArray[i].frame = 0;
        }
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

    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();

}
