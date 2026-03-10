#include "BossBattle.h"
#include "DxLib.h"

void BossBattleManager::Init(float bossX, float bossY)
{
    boss = new TutorialBoss(bossX, bossY);

    triggerX = bossX - 200;
    cameraX = bossX - 640 / 2;

    state = BOSS_NONE;
}

void BossBattleManager::Update(Player& player)
{
    if (!boss) return;

    switch (state)
    {

    case BOSS_NONE:

        if (player.GetX() > triggerX)
        {
            state = BOSS_INTRO;
        }

        break;

    case BOSS_INTRO:

        state = BOSS_BATTLE;

        break;

    case BOSS_BATTLE:

        boss->Update(player);

        cameraX = boss->GetX() - 640 / 2;

        break;

    case BOSS_DEAD:

        break;

    }
}

void BossBattleManager::Draw(float camX, float camY)
{
    if (!boss) return;

    boss->Draw(camX, camY);

    if (state == BOSS_BATTLE)
    {
        int hp = boss->GetHP();
        int maxHp = boss->GetMaxHP();

        int barWidth = 400;
        int hpWidth = barWidth * hp / maxHp;

        //í“¬‚Ì•\¦
      
    }
}

bool BossBattleManager::IsBattle() const
{
    return state == BOSS_BATTLE;
}

float BossBattleManager::GetCameraX() const
{
    return cameraX;
}