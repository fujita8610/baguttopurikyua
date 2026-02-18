#pragma once
#include "DxLib.h"
#include "../Input/Input.h"
class Player
{
public:
	Player();
    void Update(Input& input);
    void Draw(float camX);

private:
    int x, y;
    int speed;
    int image;

    float vy;
    float gravity;
    float jumpPower;

    bool isGround;
    int jumpCount;
    bool facingRight;
};

