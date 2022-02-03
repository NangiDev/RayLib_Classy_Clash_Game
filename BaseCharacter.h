#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle GetCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    const char *knightIdleFilepath = "characters/knight_idle_spritesheet.png";
    const char *knightRunFilepath = "characters/knight_run_spritesheet.png";
    Texture2D texture = LoadTexture(knightIdleFilepath);
    Texture2D idle = LoadTexture(knightIdleFilepath);
    Texture2D run = LoadTexture(knightRunFilepath);
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
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif