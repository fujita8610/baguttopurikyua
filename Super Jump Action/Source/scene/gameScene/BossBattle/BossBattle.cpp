#include "BossBattle.h"
#include "DxLib.h"
#include "../../../Enemy/EnemyCollision/EnemyCollision.h"

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

        cameraX = boss->GetX() - 640 / 2 - 96;
        state = BOSS_BATTLE;
        break;

    case BOSS_BATTLE:

        boss->SetCamera(cameraX);
        boss->Update(player);

        if (!boss->IsAlive() && boss->IsDeathFinished())
        {
            state = BOSS_DEAD;
        }

        if (boss->IsAlive())
        {
            if (player.IsAttacking())
            {
                if (EnemyCollision::CheckRect(player.GetAttackRect(), boss->GetRect()) ||
                    EnemyCollision::CheckRect(player.GetAttackRect(), boss->GetHeadRect()))
                {
                    boss->TakeDamage(1);
                }
            }

            if (boss->IsStampAttacking())
            {
                if (EnemyCollision::CheckRect(player.GetRect(), boss->GetStampAttackRect()))
                {
                    const_cast<Player&>(player).TakeDamageFromEnemy();
                }
            }

            if (EnemyCollision::CheckRect(player.GetRect(), boss->GetHeadRect()))
            {
                bool stomped = false;
                const_cast<Player&>(player).CheckEnemyCollision(boss->GetHeadRect(), stomped);
                if (stomped)
                {
                    boss->TakeDamage(1);
                }
            }
        }

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

bool BossBattleManager::IsDead() const
{
    return state == BOSS_DEAD;
}

float BossBattleManager::GetCameraX() const
{
    return cameraX;
}