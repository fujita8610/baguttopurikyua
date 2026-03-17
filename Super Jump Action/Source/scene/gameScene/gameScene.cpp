#include "DxLib.h"
#include "gameScene.h"
#include "../sceneManager.h"
#include "../title/titleScene.h"

//マップ関連
#include "../../map/manager/mapmanager.h"
#include "../../map/tileManager/tileManager.h"
#include "../../map/map.h"

void GameScene::Init()
{
    gameOver = false;

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

    if (gameOver)
    {
        if (input.IsKeyDownTrigger(KEY_INPUT_RETURN))
        {
            SceneManager::ChangeScene(new TitleScene());
            return;
        }

        input.LateUpdate();
        return;
    }

    player.Update(input);
    enemyManager.Update(player);
    bossBattle.Update(player);

    if (!player.IsAlive() && player.IsDeathAnimationFinished())
    {
        gameOver = true;
    }

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

    if (gameOver)
    {
        int screenW = 1280;
        int screenH = 720;
        GetScreenState(&screenW, &screenH, NULL);

        DrawBox(0, 0, screenW, screenH, GetColor(0, 0, 0), TRUE);
        DrawString(screenW / 2 - 60, screenH / 2 - 20, "GAME OVER", GetColor(255, 0, 0));
        DrawString(screenW / 2 - 110, screenH / 2 + 20, "PRESS ENTER TO TITLE", GetColor(255, 255, 255));
    }
}
void GameScene::End()
{
}