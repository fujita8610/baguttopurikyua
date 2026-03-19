#pragma once

#include "../../../Enemy/BossEnemy/tutorialBoss/tutorialBoss.h"
#include "../../../Player/Player.h"

enum BossState
{
    BOSS_NONE,
    BOSS_INTRO,
    BOSS_BATTLE,
    BOSS_DEAD
};

class BossBattleManager
{
public:

    void Init(float bossX, float bossY);
    void Update(Player& player);
    void Draw(float camX, float camY);

    bool IsBattle() const;
    bool IsDead() const;
    float GetCameraX() const;

private:

    TutorialBoss* boss = nullptr;

    BossState state = BossState::BOSS_NONE;

    float triggerX = 0;
    float cameraX = 0;
};