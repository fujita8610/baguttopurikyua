#pragma once
#include "DxLib.h"
#include "../Input/Input.h"
#include "../Graphics/SpriteSheet.h"
#include "../Animation/Animation.h"
class Player
{
public:
    Player();
    void Update(Input& input);
    void Draw(float camX);

    float GetX() const;
    float GetY() const;

    //初期位置
    void SetPosition(float x, float y);

private:
    //位置座標
    VECTOR pos;
    int speed;
    int image;

    int width = 32;   
    int height = 32;

    float vy;
    float gravity;
    float jumpPower;

    bool isGround;
    int jumpCount;

    // アニメーション関連
    SpriteSheet sprite;
    Animation anim;
    int totalFrames;
    enum class State { Idle, Run, Jump } state;
    bool useSpriteSheet;
};

