#pragma once
#include "../../EnemyBase/BossBase.h"
#include "../../../Graphics/SpriteSheet.h"
#include "../../../Animation/Animation.h"

class TutorialBoss : public BossBase
{
public:
    TutorialBoss(float x, float y);

    void Update(const Player& player) override;
    void Draw(float camX, float camY) override;
    Rect GetRect() const override;

private:

    enum class State
    {
        Idle,
        FlagBlack,
        FlagRed,
        FlagYellow,

        Wait,

        Stamp,

        DashStart,
        DashLoop,
        DashEnd
    };

    State state;

    SpriteSheet idle;

    SpriteSheet flagBlack;
    SpriteSheet flagRed;
    SpriteSheet flagYellow;

    SpriteSheet stamp;

    SpriteSheet dashStart;
    SpriteSheet dashLoop;
    SpriteSheet dashEnd;

    Animation anim;

    int direction = -1;

    int waitTimer = 0;

    float dashSpeed = 8.0f;

    void ChangeState(State newState);
};