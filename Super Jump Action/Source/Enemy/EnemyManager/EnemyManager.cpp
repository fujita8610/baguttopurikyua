#include "EnemyManager.h"
#include "../EnemyBase/EnemyBase.h"
#include <algorithm>

void EnemyManager::Update(const Player& player)
{
    // ‘S“G‚ÌXV
    for (auto& enemy : enemies)
    {
        enemy->Update(player);
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

Rect EnemyBase::GetRect() const
{
    Rect r;

    int hitWidth = 40;
    int hitHeight = 40;

    r.left = (int)x - hitWidth / 2;
    r.right = (int)x + hitWidth / 2;

    // ­‚µ‰º‚É‚¸‚ç‚·
    r.top = (int)y - hitHeight / 2 + 20;
    r.bottom = (int)y + hitHeight / 2 + 20;

    return r;
}