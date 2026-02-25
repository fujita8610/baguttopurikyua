#include "DxLib.h"

//scene関連
#include "titleScene.h"
#include "../sceneManager.h"
#include "../../scene/gameScene/gameScene.h"

void TitleScene::Init()
{

}

void TitleScene::Update()
{
    input.Update();

    // Enterキーでゲーム開始
    if (input.IsKeyDownTrigger(KEY_INPUT_RETURN))
    {
        SceneManager::ChangeScene(new GameScene());
        return;
    }
}

void TitleScene::Draw()
{
    DrawString(200, 200, "SUPER JUMP ACTION", GetColor(255, 255, 255));
    DrawString(220, 260, "PRESS ENTER", GetColor(255, 255, 255));
}

void TitleScene::End()
{

}