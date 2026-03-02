#include "GameDebug.h"
#include "DxLib.h"
#include "../Input/Input.h"

bool GameDebug::debug = false;

void GameDebug::Update(Input& input)
{
    //F1でデバックを表示
    if (input.IsKeyDownTrigger(KEY_INPUT_F1))
    {
        debug = !debug;
    }
}



bool GameDebug::IsDebug()
{
    return debug;
}