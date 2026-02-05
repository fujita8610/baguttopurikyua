#include "TitleScene.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"

int g_TitleBGHandle = -1;
int g_TitleTextHandle = -1;
int g_TitleOptionHandle = -1;

void InitTitleScene()
{
}

void LoadTitleScene()
{
	g_TitleBGHandle = LoadGraph("Data/Title/BG.png");
	g_TitleTextHandle = LoadGraph("Data/Title/TitleText.png");
	g_TitleOptionHandle = LoadGraph("Data/Title/TitleOption.png");
}

void StartTitleScene()
{
}

void StepTitleScene()
{
	if (IsTriggerKey(KEY_Z))
	{
		ChangeScene(SCENE_PLAY);
	}
	else if (IsTriggerKey(KEY_X))
	{
		ChangeScene(SCENE_OPTION);
	}
}

void UpdateTitleScene()
{
}

void DrawTitleScene()
{
	DrawGraph(0, 0, g_TitleBGHandle, TRUE);
	DrawGraph(200, 200, g_TitleTextHandle, TRUE);
	DrawGraph(200, 600, g_TitleOptionHandle, TRUE);
}

void FinTitleScene()
{
	DeleteGraph(g_TitleBGHandle);
	DeleteGraph(g_TitleTextHandle);
}

