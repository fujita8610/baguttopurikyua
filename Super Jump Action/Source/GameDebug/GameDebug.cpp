#include "GameDebug.h"
#include "DxLib.h"

bool GameDebug::debug = false;

void GameDebug::Update()
{
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