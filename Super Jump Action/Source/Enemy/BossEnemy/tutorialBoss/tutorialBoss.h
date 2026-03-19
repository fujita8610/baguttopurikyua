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
    void TakeDamage(int damage) override;

    Rect GetRect() const override;
    Rect GetHeadRect() const;
    Rect GetStampAttackRect() const;

    bool IsStampAttacking() const { return stampAttacking; }
    bool IsDeathFinished() const { return deathTimer >= DEATH_DURATION; }

    void SetCamera(float camX) { camXRef = camX; }

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

    float dashSpeed = 4.0f;

    void ChangeState(State newState);

    bool idleRolled = false;

    float camXRef = 0.0f;

    bool stampAttacking = false;

    int idleTimer = 0;

    bool isDying = false;

    int deathTimer = 0;

    int dashFlashTimer = 0;

    const int DEATH_DURATION = 120;

    bool isEnraged = false;
};