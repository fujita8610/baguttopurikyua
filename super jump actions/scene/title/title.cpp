#include "titlescene.h"
#include "../../Input/Input.h"
#include "../SceneManager.h"
#include "DxLib.h"

#include "../play/playscene.h"




void TitleScene::Init()
{
    titleImage = LoadGraph("data/image/title.png");

    pushKeyFlash = 0;
}




void TitleScene::Update()
{
    pushKeyFlash++;

    // スペースキーでゲーム開始
    if (Input::IsKeyTrigger(KEY_INPUT_SPACE))
    {
        SceneManager::ChangeScene(new PlayScene());
    }
}




void TitleScene::Draw()
{
    // タイトル画像
    DrawGraph(0, 0, titleImage, TRUE);


    // 点滅文字
    if ((pushKeyFlash / 30) % 2 == 0)
    {
        DrawString(300, 400, "PRESS SPACE KEY", GetColor(255, 255, 255));
    }
}




void TitleScene::End()
{
    DeleteGraph(titleImage);
}
