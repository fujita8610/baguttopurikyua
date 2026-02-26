#pragma once
#include "DxLib.h"

//入力
#include "../Input/Input.h"
#include "../System/cooldown.h"

//アニメーション関連
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

    bool IsJumping() const;

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

    //通常 cpp/.h での宣言を兼用
    Cooldown jumpCooldown;

    // アニメーション関連
    SpriteSheet spriteIdle;   // Idle用
    SpriteSheet spriteRun;    // Run用
    SpriteSheet spriteJump;   // Jump用(上昇)
    SpriteSheet spriteFall;   // Fall用(落下)
    
    Animation anim;
    
    int idleFrames;
    int runFrames;
    int jumpFrames;
    int fallFrames;
    
    enum class State { Idle, Run, Jump, Fall } state;
    bool useSpriteSheet;

    // 向き（true = 右向き、false = 左向き）
    bool facingRight;
};

