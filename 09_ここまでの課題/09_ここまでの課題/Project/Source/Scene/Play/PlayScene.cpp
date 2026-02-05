#include "PlayScene.h"
#include "../../Input/Input.h"
#include "../SceneManager.h"

int g_PlayBGHandle = -1;
CharacterData g_CharacterData[CHARACTER_TYPE_MAX] = {};

const float PLAYER_SPEED = 5.0f;


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

	if (CheckHitKey(KEY_INPUT_UP))
	{
		player.pos.y -= PLAYER_SPEED;
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		player.pos.y += PLAYER_SPEED;
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player.pos.x -= PLAYER_SPEED;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		player.pos.x += PLAYER_SPEED;
	}

}

void DrawPlayScene()
{
	DrawGraph(0, 0, g_PlayBGHandle, TRUE);

	for (int i = 0; i < CHARACTER_TYPE_MAX; i++)
	{
		DrawGraph((int)g_CharacterData[i].pos.x, (int)g_CharacterData[i].pos.y, g_CharacterData[i].handle, TRUE);
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

