#pragma once
#include <vector>
#include <memory>
#include "../../Player/Player.h"

//マップ関連
#include "../../map/tileManager/tileManager.h"

class EnemyBase;

class EnemyManager
{
public:
	void Update(const Player& player);
	void Draw(float camX, float camY);

	void AddEnemy(std::unique_ptr<EnemyBase> enemy);

    //敵の配置のテンプレート（座標管理）作：藤田
    template<class T>
    void AddEnemyTile(int tileX, int tileY)
    {
        float scale = TileManager::GetScale();
        float tileSize = TILE_SIZE * scale;

        float x = tileX * tileSize;
        float y = tileY * tileSize;

        AddEnemy(std::make_unique<T>(x, y));
    }

private:
	std::vector<std::unique_ptr<EnemyBase>> enemies;
};