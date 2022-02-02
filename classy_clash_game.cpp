#include <string.h>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

const int WIDTH = 384;
const int HEIGHT = 384;
const char *TITLE = "Classy Clash";
const int FPS = 60;
const float mapScale{4.0f};

const char *mapFilepath = "nature_tileset/WorldMap6x6.png";

int main()
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    Texture2D map = LoadTexture(mapFilepath);
    Vector2 mapPos{0.0, 0.0};

    Character knight(WIDTH, HEIGHT);
    Prop props[2]{
        Prop{LoadTexture("nature_tileset/Rock.png"), Vector2{200.f, 300.f}},
        Prop{LoadTexture("nature_tileset/Log.png"), Vector2{300.f, 500.f}}};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        const float dT{GetFrameTime()};

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        knight.tick(dT);
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + WIDTH > map.width * mapScale ||
            knight.getWorldPos().y + HEIGHT > map.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(knight.GetCollisionRec(), prop.GetCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }

        // DrawText(TextFormat("%d, %d", knight.getWorldPos().x, knight.getWorldPos().y), 0, 0, 60, RED);

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();
    return 0;
}