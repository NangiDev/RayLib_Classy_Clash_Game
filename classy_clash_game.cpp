#include <string.h>
#include "raylib.h"
#include "raymath.h"

const int WIDTH = 384;
const int HEIGHT = 384;
const char *TITLE = "Classy Clash";
const int FPS = 60;

const char *mapFilepath = "map/WorldMap.png";
const char *knightIdleFilepath = "characters/knight_idle_spritesheet.png";
const char *knightRunFilepath = "characters/knight_run_spritesheet.png";

int main()
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    Texture2D map = LoadTexture(mapFilepath);
    Vector2 mapPos{0, 0};
    float speed{4.0};

    Texture2D knight = LoadTexture(knightIdleFilepath);
    Texture2D knight_idle = LoadTexture(knightIdleFilepath);
    Texture2D knight_run = LoadTexture(knightRunFilepath);

    float rightLeft{1.0f};
    Vector2 knightPos{
        (float)WIDTH / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
        (float)HEIGHT / 2.0f - 4.0f * (0.5f * (float)knight.height)};
    Rectangle destRect{
        knightPos.x, knightPos.y,
        4.0f * (float)knight.width / 6.0f,
        4.0f * (float)knight.height};

    float runningTime{};
    float frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        const float dT{GetFrameTime()};

        Vector2 direction{};
        if (IsKeyDown(KEY_A))
            direction.x -= 1.0;
        if (IsKeyDown(KEY_D))
            direction.x += 1.0;
        if (IsKeyDown(KEY_W))
            direction.y -= 1.0;
        if (IsKeyDown(KEY_S))
            direction.y += 1.0;

        knight = knight_idle;
        if (Vector2Length(direction) != 0.0)
        {
            knight = knight_run;
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        }

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        runningTime += dT;
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames)
            {
                frame = 0;
            }
        }

        Rectangle sourceRect{
            frame * (float)knight.width / 6.0f, 0,
            rightLeft * (float)knight.width / 6.0f,
            (float)knight.height};

        DrawTexturePro(knight, sourceRect, destRect, {0, 0}, 0.0f, WHITE);

        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(knight_idle);
    UnloadTexture(knight_run);

    CloseWindow();
    return 0;
}