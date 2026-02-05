#include "PlayScene.h"
#include "../../Input/Input.h"
#include "../SceneManager.h"
#include <cstdlib>   // rand
#include <ctime>     // time


int g_PlayBGHandle = -1;
CharacterData g_CharacterData[CHARACTER_TYPE_MAX] = {};


const float PLAYER_SPEED = 5.0f;

struct Bullet
{
	VECTOR pos;
	bool isActive;
};

const int BULLET_MAX = 32;
Bullet g_Bullets[BULLET_MAX];

const float BULLET_SPEED = 10.0f;
const float BULLET_R = 5.0f;


//当たり判定のブール
bool IsHitRect(
	float ax, float ay, float aw, float ah,
	float bx, float by, float bw, float bh)
{
	return ax < bx + bw &&
		ax + aw > bx &&
		ay < by + bh &&
		ay + ah > by;
}

const float ENEMY_W = 64.0f;
const float ENEMY_H = 64.0f;




void InitPlayScene()
{
}

void LoadPlayScene()
{
	g_PlayBGHandle = LoadGraph("Data/Play/BG.png");

	g_CharacterData[CHARACTER_TYPE_HERO].handle = LoadGraph("Data/Player/Player.png");
	g_CharacterData[CHARACTER_TYPE_ENEMY_A].handle = LoadGraph("Data/Enemy/DragonFly.png");
	g_CharacterData[CHARACTER_TYPE_ENEMY_B].handle = LoadGraph("Data/Enemy/Flies.png");
}

void StartPlayScene()
{
	g_CharacterData[CHARACTER_TYPE_HERO].pos = VGet(100.0f, 100.0f, 0.0f);
	g_CharacterData[CHARACTER_TYPE_ENEMY_A].pos = VGet(800.0f, 200.0f, 0.0f);
	g_CharacterData[CHARACTER_TYPE_ENEMY_B].pos = VGet(900.0f, 600.0f, 0.0f);

	// 乱数初期化（1回だけでOKだが簡易的にここで）
	srand((unsigned int)time(nullptr));

	// 弾初期化
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullets[i].isActive = false;
	}

}

void StepPlayScene()
{
	if (IsTriggerKey(KEY_C))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void UpdatePlayScene()
{

		CharacterData& player = g_CharacterData[CHARACTER_TYPE_HERO];

		// ===== プレイヤー移動 =====
		if (CheckHitKey(KEY_INPUT_UP))
			player.pos.y -= PLAYER_SPEED;

		if (CheckHitKey(KEY_INPUT_DOWN))
			player.pos.y += PLAYER_SPEED;

		if (CheckHitKey(KEY_INPUT_LEFT))
			player.pos.x -= PLAYER_SPEED;

		if (CheckHitKey(KEY_INPUT_RIGHT))
			player.pos.x += PLAYER_SPEED;

		// ===== 弾発射 =====
		if (CheckHitKey(KEY_INPUT_Z))
		{
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (!g_Bullets[i].isActive)
				{
					g_Bullets[i].isActive = true;
					g_Bullets[i].pos = player.pos;
					break;
				}
			}
		}

		// ===== 弾移動 =====
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (!g_Bullets[i].isActive) continue;

			g_Bullets[i].pos.x += BULLET_SPEED;

			if (g_Bullets[i].pos.x > 1280)
			{
				g_Bullets[i].isActive = false;
			}
		}

		// ===== 敵ランダム移動 =====
		CharacterData& enemy = g_CharacterData[CHARACTER_TYPE_ENEMY_A];

		int r = rand() % 4;
		const float ENEMY_SPEED = 2.0f;

		if (r == 0) enemy.pos.x += ENEMY_SPEED;
		if (r == 1) enemy.pos.x -= ENEMY_SPEED;
		if (r == 2) enemy.pos.y += ENEMY_SPEED;
		if (r == 3) enemy.pos.y -= ENEMY_SPEED;




		// ===== 当たり判定 =====
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (!g_Bullets[i].isActive) continue;

			if (IsHitRect(
				g_Bullets[i].pos.x - BULLET_R,
				g_Bullets[i].pos.y - BULLET_R,
				BULLET_R * 2,
				BULLET_R * 2,
				enemy.pos.x,
				enemy.pos.y,
				ENEMY_W,
				ENEMY_H))
			{
				// 弾を消す
				g_Bullets[i].isActive = false;

				// 敵を画面外へ（仮処理）
				enemy.pos = VGet(900.0f, rand() % 600, 0.0f);
			}
		}

	}

void DrawPlayScene()
{
	DrawGraph(0, 0, g_PlayBGHandle, TRUE);

	for (int i = 0; i < CHARACTER_TYPE_MAX; i++)
	{
		DrawGraph((int)g_CharacterData[i].pos.x,
			(int)g_CharacterData[i].pos.y,
			g_CharacterData[i].handle, TRUE);
	}

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullets[i].isActive)
		{
			DrawCircle(
				(int)g_Bullets[i].pos.x,
				(int)g_Bullets[i].pos.y,
				5,
				GetColor(255, 255, 0),
				TRUE
			);
		}
	}

}

void FinPlayScene()
{
	DeleteGraph(g_PlayBGHandle);

	for (int i = 0; i < CHARACTER_TYPE_MAX; i++)
	{
		DeleteGraph(g_CharacterData[i].handle);
	}
}

