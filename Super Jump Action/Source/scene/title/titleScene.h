#pragma once
#include "../scene.h"
#include "../../Input/Input.h"

//アニメーション関連
#include "../../Graphics/SpriteSheet.h"
#include "../../Animation/Animation.h"


class TitleScene : public Scene
{

    public:
        void Init() override;
        void Update() override;
        void Draw() override;
        void End() override;

    private:
        Input input;
        


        //画像ハンドル
        int titleFrameHandle = -1;
        int selectBarHandle = -1;


        int cursor = 0;   // 選択位置
        static const int MENU_MAX = 4; //選択母数

        //タイマー
        int blinkTimer = 0;

        //走るアニメーション
        SpriteSheet playerRun;
        Animation playerAnim;
        int playerFrames; 

        //待機モーション
        SpriteSheet playerIdle;
        Animation playerIdleAnim;
        int idleFrames;
};