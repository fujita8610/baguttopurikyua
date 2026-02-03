#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"

int g_OptionBGHandle = -1;
int g_OptionTextHandle = -1;
int g_BGMTextHandle = -1;
int g_SETextHandle = -1;
int g_GaugeHandle = -1;

void InitOptionScene()
{
	g_OptionBGHandle = -1;
	g_OptionTextHandle = -1;
	g_BGMTextHandle = -1;
	g_SETextHandle = -1;
	g_GaugeHandle = -1;
}

void LoadOptionScene()
{
	g_OptionBGHandle = LoadGraph("Data/Option/BG.png");
	g_OptionTextHandle = LoadGraph("Data/Option/Option.png");
	g_BGMTextHandle = LoadGraph("Data/Option/BGM.png");
	g_SETextHandle = LoadGraph("Data/Option/SE.png");
	g_GaugeHandle = LoadGraph("Data/Option/Gauge.png");
}

void StartOptionScene()
{
}

void StepOptionScene()
{
	if (IsTriggerKey(KEY_C))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void UpdateOptionScene()
{
}

void DrawOptionScene()
{
	DrawGraph(0, 0, g_OptionBGHandle, TRUE);
	DrawGraph(600, 50, g_OptionTextHandle, TRUE);
	DrawGraph(200, 280, g_BGMTextHandle, TRUE);
	DrawGraph(200, 480, g_SETextHandle, TRUE);
	DrawGraph(600, 250, g_GaugeHandle, TRUE);
	DrawGraph(600, 450, g_GaugeHandle, TRUE);
}

void FinOptionScene()
{
	DeleteGraph(g_OptionBGHandle);
	DeleteGraph(g_OptionTextHandle);
	DeleteGraph(g_BGMTextHandle);
	DeleteGraph(g_SETextHandle);
	DeleteGraph(g_GaugeHandle);
}

