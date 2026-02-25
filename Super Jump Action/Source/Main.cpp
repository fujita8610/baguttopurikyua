#include "DxLib.h"
#include "Player/Player.h"
#include "Input/Input.h"
#include "Camera/Camera.h"

#include "../Source/Enemy/EnemyManager/EnemyManager.h"
#include "../Source/Enemy/MushroomReg/MushroomReg.h"


//マップ関連
#include "map/manager/mapmanager.h"
#include "map/tileManager/tileManager.h"
#include "map/map.h"
#include <stdio.h>

//ゲームデバッグ
#include "../Source/GameDebug/GameDebug.h"


int main()
{
	// DxLibの初期化
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	Player player;


	Input input;

	// タイルロード
	TileManager::LoadTiles("Data/Map/1985_tiles.png", 8, 8);

	// 拡大率設定 (倍率）
	TileManager::SetScale(4.0f);

    // マップロード
	MapManager::Init();

	//プレイヤーの設置
	player.SetPosition(5, 10);

	//Enemyマネージャー
	EnemyManager enemyManager;

	// CSVからEnemy生成
	for (int i = 0; i < g_EnemyCount; i++)
	{
		enemyManager.AddEnemyTile<MushroomReg>(
			g_EnemyStartX[i],
			g_EnemyStartY[i]
		);
	}

	while (true) 
	{
		input.Update();
		GameDebug::Update();
		if (input.IsKeyDown(KEY_INPUT_ESCAPE)) break;

		player.Update(input);
		UpdateCamera(player.GetX(), player.GetY());

		enemyManager.Update();

		ClearDrawScreen();

		// マップ描画
		MapManager::Draw();


		enemyManager.Draw();

		player.Draw(0); // カメラ位置は0で固定
		ScreenFlip();
		input.LateUpdate();
	}
	DxLib_End();
	return 0;
}