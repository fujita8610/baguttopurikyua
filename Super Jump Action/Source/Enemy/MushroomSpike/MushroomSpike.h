#pragma once
#include "../EnemyBase/EnemyBase.h"
#include "../../Animation/Animation.h"
#include "../../Graphics/SpriteSheet.h"


class MushroomSpike : public EnemyBase
{
public:
    MushroomSpike(float startX, float startY);

    void Update(const Player& player);
    void Draw(float camX, float camY) override;
    Rect GetRect() const override;

    // 踏まれ判定を無視する（トゲなので踏んでもダメージなし）
    bool IsInvulnerableToStomp() const override { return true; }

private:
    SpriteSheet sprite;
    Animation walkAnim;
    Animation spikeAnim;

    int divX = 10;
    int walkRow = 1;   // 歩行行
    int spikeRow = 3;  // トゲ行

    float speed = 2.0f;
    int dir = 1;

    bool spikeActive = false;
};