#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

const int WIDTH = 384;
const int HEIGHT = 384;
const char *TITLE = "Classy Clash";
const int FPS = 60;
const float mapScale{4.0f};

const char *mapFilepath = "nature_tileset/OpenWorldMap24x24.png";

int main()
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    Texture2D map = LoadTexture(mapFilepath);
    Vector2 mapPos{0.0, 0.0};

    Character knight(WIDTH, HEIGHT);
    Prop props[2]{
        Prop{Vector2{200.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{300.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin = Enemy{
        Vector2{500.f, 500.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime =
        Enemy{
            Vector2{300.f, 600.f},
            LoadTexture("characters/slime_idle_spritesheet.png"),
            LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[2]{&goblin, &slime};

    for (auto e : enemies)
    {
        e->setTarget(&knight);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        const float dT{GetFrameTime()};

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

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

        for (auto e : enemies)
        {
            e->tick(dT);
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto e : enemies)
            {
                if (CheckCollisionRecs(e->GetCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    e->setAlive(false);
                }
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}