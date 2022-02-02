#include "Prop.h"
#include "raymath.h"

Prop::Prop(Texture2D tex, Vector2 pos) : texture(tex), worldPos(pos)
{
}

Prop::~Prop()
{
    UnloadTexture(texture);
}

void Prop::Render(Vector2 knigtPos)
{
    screenPos = Vector2Subtract(worldPos, knigtPos);
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}