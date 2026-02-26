#pragma once
#include "../EnemyBase/EnemyBase.h"
#include "../../Animation/Animation.h"
#include "../../Graphics/SpriteSheet.h"


class MushroomSpike : public EnemyBase
{
public:
    MushroomSpike(float startX, float startY);

    void Update(bool playerIsJumping);
    void Draw() override;
    Rect GetRect() const override;

private:
    SpriteSheet sprite;
    Animation walkAnim;
    Animation spikeAnim;

    int divX = 10;
    int walkRow = 1;   // 歩行段
    int spikeRow = 3;  // トゲ段

    float speed = 2.0f;
    int dir = 1;

    bool spikeActive = false;
};