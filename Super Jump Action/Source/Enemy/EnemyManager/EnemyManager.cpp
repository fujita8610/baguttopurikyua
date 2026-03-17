#include "EnemyManager.h"
#include "../EnemyBase/EnemyBase.h"
#include "../EnemyCollision/EnemyCollision.h"
#include <algorithm>

void EnemyManager::Update(const Player& player)
{
    Rect playerRect = player.GetRect();
    Rect playerAttackRect = player.GetAttackRect();

    // 全敵の更新
    for (auto& enemy : enemies)
    {
        enemy->Update(player);

        if (!player.IsAlive()) continue;

        Rect enemyRect = enemy->GetRect();

        // プレイヤーの攻撃判定とエネミーが接触しているか
        if (player.IsAttacking() && EnemyCollision::CheckRect(playerAttackRect, enemyRect))
        {
            // 敵にダメージを与える（倒す）
            enemy->TakeDamage(1);
        }
        else
        {
            // プレイヤーとエネミーが接触しているか
            if (EnemyCollision::CheckRect(playerRect, enemyRect))
            {
                // 踏まれ判定を無視する敵（トゲなど）の場合
                if (enemy->IsInvulnerableToStomp())
                {
                    // 常にプレイヤーが死ぬ
                    const_cast<Player&>(player).TakeDamageFromEnemy();
                }
                else
                {
                    bool enemyStomped = false;
                    const_cast<Player&>(player).CheckEnemyCollision(enemyRect, enemyStomped);

                    if (enemyStomped)
                    {
                        // 敵を倒す
                        enemy->TakeDamage(1);
                    }
                }
            }
        }
    }

    // 死んだ敵を削除
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
    // 全敵の描画
    for (auto& enemy : enemies)
    {
        enemy->Draw(camX, camY);
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

    // 少し下にずらす
    r.top = (int)y - hitHeight / 2 + 20;
    r.bottom = (int)y + hitHeight / 2 + 20;

    return r;
}