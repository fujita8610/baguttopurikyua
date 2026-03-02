#include "EnemyManager.h"
#include "../EnemyBase/EnemyBase.h"
#include <algorithm>

void EnemyManager::Update(bool playerIsJumping)
{
    // ‘S“G‚ÌXV
    for (auto& enemy : enemies)
    {
        enemy->Update(playerIsJumping);
    }

    // €–S‚µ‚½“G‚ğíœ
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<EnemyBase>& enemy)
            {
                return !enemy->IsAlive();
            }),
        enemies.end()
                );
}

void EnemyManager::Draw(float camX, float camY)
{
    // ‘S“G‚Ì•`‰æ
    for (auto& enemy : enemies)
    {
        enemy->Draw(camX,camY);
    }
}

void EnemyManager::AddEnemy(std::unique_ptr<EnemyBase> enemy)
{
    enemies.push_back(std::move(enemy));
}