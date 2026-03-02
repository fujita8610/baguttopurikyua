#include "GameDebug.h"
#include "DxLib.h"

bool GameDebug::debug = false;
Cooldown GameDebug::toggleCooldown;

void GameDebug::Update()
{
    //クールダウンを追加
    toggleCooldown.Set(20);
    toggleCooldown.Update();

    //F1でデバッグの表示
    if (CheckHitKey(KEY_INPUT_F1))
    {
        debug = !debug;
    }
}

bool GameDebug::IsDebug()
{
    return debug;
}