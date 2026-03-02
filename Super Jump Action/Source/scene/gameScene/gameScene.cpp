#include "DxLib.h"
#include "gameScene.h"

//マップ関連
#include "../../map/manager/mapmanager.h"
#include "../../map/tileManager/tileManager.h"
#include "../../map/map.h"


void GameScene::Init()
{
    // タイル
    TileManager::LoadTiles("Data/Map/1985_tiles.png", 8, 8);

    //拡大関数
    TileManager::SetScale(4.0f);

    // マップ
    MapManager::Init();

    // プレイヤー初期位置
    player.SetPosition(
        g_PlayerStartX,
        g_PlayerStartY
    );

    // CSVからEnemy生成
    for (int i = 0; i < g_EnemyCount; i++)
    {
        switch (g_EnemyType[i])
        {
        case TILE_ENEMY1_START:   // 97
            enemyManager.AddEnemyTile<MushroomReg>(
                g_EnemyStartX[i],
                g_EnemyStartY[i]
            );
            break;

        case TILE_ENEMY2_START:   // 96
            enemyManager.AddEnemyTile<MushroomSpike>(
                g_EnemyStartX[i],
                g_EnemyStartY[i]
            );
            break;
        }

    }
}

void GameScene::Update()
{
    input.Update();

    if (input.IsKeyDown(KEY_INPUT_ESCAPE))
    {
        DxLib_End();
        exit(0);
    }

    //動くもの更新
    player.Update(input);
    enemyManager.Update(player.IsJumping());

    // カメラ更新
    cameraX = player.GetX() - 640 / 2;
    cameraY = player.GetY() - 360 / 2;
    // マイナス防止
    if (cameraX < 0) cameraX = 0;
    if (cameraY < 0) cameraY = 0;
}

void GameScene::Draw()
{
    DrawMap(cameraX, cameraY);
    enemyManager.Draw(cameraX,cameraY);
    player.Draw(cameraX, cameraY);
}
void GameScene::End()
{
}