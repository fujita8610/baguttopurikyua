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

    //プレイヤー大きさ倍率
    player.SetScale(1.7f);

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

        //case TILE_ENEMY3_START:   // 95
        //    enemyManager.AddEnemyTile<>(
        //        g_EnemyStartX[i],
        //        g_EnemyStartY[i]
        //    );
        //    break;

        //case TILE_ENEMY4_START:   // 94
        //    enemyManager.AddEnemyTile<>(
        //        g_EnemyStartX[i],
        //        g_EnemyStartY[i]
        //    );
        //    break;

        //case TILE_ENEMY5_START:   // 93
        //    enemyManager.AddEnemyTile<>(
        //        g_EnemyStartX[i],
        //        g_EnemyStartY[i]
        //    );
        //    break;

        //case TILE_ENEMY6_START:   // 92
        //    enemyManager.AddEnemyTile<>(
        //        g_EnemyStartX[i],
        //        g_EnemyStartY[i]
        //    );
        //    break;

        }

    }

    //ボス生成
    if (g_BossExist)
    {
        float scale = TileManager::GetScale();

        float bossX = g_BossStartX * TILE_SIZE * scale;
        float bossY = g_BossStartY * TILE_SIZE * scale - 60;

        bossBattle.Init(bossX, bossY);
    }

   
    //ボス戦移行
    bossTriggerX = g_BossStartX * TILE_SIZE * TileManager::GetScale() - 100;
    bossTriggerY = g_BossStartY * TILE_SIZE * TileManager::GetScale() -100;

  
    
}

void GameScene::Update()
{
    input.Update();
    GameDebug::Update(input);


    if (input.IsKeyDown(KEY_INPUT_ESCAPE))
    {
        DxLib_End();
        exit(0);
    }

        // プレイヤーが生存しているかチェック
    if (!player.IsAlive())
    {
        // ゲームオーバー処理（ここでは簡単にゲーム終了）
        DxLib_End();
        exit(0);
    }

    //プレイヤーの更新
    player.Update(input);
    enemyManager.Update(player);

    //ボス戦開始
    bossBattle.Update(player);

  //====================
  // カメラ更新
  //====================

    int screenW, screenH;
    GetScreenState(&screenW, &screenH, NULL);

    if (bossBattle.IsBattle())
    {
        float targetX = bossBattle.GetCameraX();

        // スムーズ移動
        cameraX += (targetX - cameraX) * 0.04f;
    }
    else
    {
        cameraX = player.GetX() - screenW / 2;
    }

    cameraY = player.GetY() - screenH / 2;

    // マイナス防止
    if (cameraX < 0) cameraX = 0;
    if (cameraY < 0) cameraY = 0;

    // マップ境界
    float mapWidth = MAP_WIDTH * TILE_SIZE * TileManager::GetScale();
    float mapHeight = MAP_HEIGHT * TILE_SIZE * TileManager::GetScale();

    if (cameraX > mapWidth - screenW)
    {
        cameraX = mapWidth - screenW;
    }

    if (cameraY > mapHeight - screenH)
    {
        cameraY = mapHeight - screenH;
    }
  
    //クールダウン更新
    input.LateUpdate();
}

void GameScene::Draw()
{
    DrawMap(cameraX, cameraY);
    enemyManager.Draw(cameraX,cameraY);
    player.Draw(cameraX, cameraY);
    bossBattle.Draw(cameraX, cameraY);
}
void GameScene::End()
{
}