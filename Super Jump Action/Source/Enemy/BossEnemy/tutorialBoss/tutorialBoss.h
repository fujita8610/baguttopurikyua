#pragma once
#include "../../../Enemy/EnemyBase/BossBase.h"
#include "../../../Graphics/SpriteSheet.h"
#include "../../../Animation/Animation.h"

class TutorialBoss : public BossBase
{
public:
    TutorialBoss(float startX, float startY, int left, int right);

    void Update(float playerX) override;
    void Draw() override;
    Rect GetRect() const override;

    bool IsAttacking() const;

private:
    enum class State
    {
        Idle,
        ShowFlag,
        Rush,
        Stomp
    };

    State state = State::Idle;

    SpriteSheet sprite;
    Animation anim;

    int timer = 0;

    int dir = 1;
    float rushSpeed = 8.0f;

    int stageLeft;
    int stageRight;

    int flagType = 0;      // 0=çï 1=ê‘ 2=â©
    bool isAttacking = false;
};