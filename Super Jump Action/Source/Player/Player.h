#pragma once
#include "DxLib.h"
#include "../Input/Input.h"
class Player
{
public:
	Player();
    void Update(Input& input);
    void Draw(float camX);

    //‰ŠúˆÊ’u
    void SetPosition(float x, float y);

private:
    //ˆÊ’uÀ•W
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
    bool facingRight;
};

