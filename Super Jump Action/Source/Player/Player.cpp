#include "Player.h"

Player::Player()
{
	pos.x = 100;
	pos.y = 300;
	speed = 5;
	image = LoadGraph(TEXT("Data/Player/Sprites/IDLE.png"));
	vy = 0.0f;
	gravity = 0.5f;
	jumpPower = -10.0f;
	isGround = false;
	jumpCount = 0;
}

void Player::Update(Input& input) {
	if (input.IsKeyDown(KEY_INPUT_A))
	{
		pos.x -= speed;
	}

	if (input.IsKeyDown(KEY_INPUT_D))
	{
		pos.x += speed;
	}

	if (input.IsKeyDownTrigger(KEY_INPUT_SPACE) && jumpCount < 2)
	{
		vy = jumpPower;

		jumpCount++;
	}

	vy += gravity;

	pos.y += vy;
	
}


void Player::Draw(float camX)
{

	int drawX = (int)(pos.x - camX);

	int drawY = (int)pos.y;

	DrawGraph(drawX, drawY, image, TRUE);

}
void Player::SetPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;
}