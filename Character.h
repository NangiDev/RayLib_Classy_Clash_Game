#include "raylib.h"

class Character
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle GetCollisionRec();

private:
    const char *knightIdleFilepath = "characters/knight_idle_spritesheet.png";
    const char *knightRunFilepath = "characters/knight_run_spritesheet.png";
    Texture2D texture = LoadTexture(knightIdleFilepath);
    Texture2D idle = LoadTexture(knightIdleFilepath);
    Texture2D run = LoadTexture(knightRunFilepath);
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    float rightLeft{1.0};
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.0f};
    float width{};
    float height{};
    float scale{4.0f};
};