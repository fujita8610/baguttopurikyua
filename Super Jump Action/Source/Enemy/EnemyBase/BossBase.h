#pragma once
#include "EnemyBase.h"

enum class BossPhase
{
    Intro,
    Battle,
    Dead
};

class BossBase : public EnemyBase
{
public:
    BossBase(float startX, float startY, int maxHp)
    {
        x = startX;
        y = startY;

        this->maxHp = maxHp;
        hp = maxHp;

        isAlive = true;
        phase = BossPhase::Intro;
    }

    virtual ~BossBase() = default;

    virtual void Update(const Player& player) override = 0;
    virtual void Draw(float camX, float camY) override = 0;
    virtual Rect GetRect() const override = 0;

    void TakeDamage(int damage)
    {
        if (!isAlive) return;
        if (invincibleTimer > 0) return;

        hp -= damage;

        if (hp <= 0)
        {
            hp = 0;
            isAlive = false;
            phase = BossPhase::Dead;
        }

        invincibleTimer = 30;
    }

    int GetHP() const { return hp; }
    int GetMaxHP() const { return maxHp; }
    BossPhase GetPhase() const { return phase; }

protected:
    int maxHp;
    BossPhase phase = BossPhase::Intro;
    int invincibleTimer = 0;
};