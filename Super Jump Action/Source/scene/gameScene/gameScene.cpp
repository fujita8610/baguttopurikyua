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
        g_PlayerStartX * TILE_SIZE * TileManager::GetScale(),
        g_PlayerStartY * TILE_SIZE * TileManager::GetScale()
    );
}

void GameScene::Update()
{
    input.Update();

    if (input.IsKeyDown(KEY_INPUT_ESCAPE))
    {
        DxLib_End();
        exit(0);
    }

    player.Update(input);
}

void GameScene::Draw()
{
    MapManager::Draw();
    player.Draw(0);
}

void GameScene::End()
{
}