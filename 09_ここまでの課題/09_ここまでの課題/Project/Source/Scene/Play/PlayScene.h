#pragma once
#include "DxLib.h"

enum CharacterType
{
	CHARACTER_TYPE_HERO,
	CHARACTER_TYPE_ENEMY_A,
	CHARACTER_TYPE_ENEMY_B,
	CHARACTER_TYPE_MAX
};

struct CharacterData
{
	int handle;
	VECTOR pos;
};

// 関数のプロトタイプ宣言
void InitPlayScene();
void LoadPlayScene();
void StartPlayScene();
void StepPlayScene();
void UpdatePlayScene();
void DrawPlayScene();
void FinPlayScene();
