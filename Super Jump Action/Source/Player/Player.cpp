#include "Player.h"

Player::Player()
{
	x = 100;
	y = 300;
	speed = 5;
	image = LoadGraph(TEXT("Data/Player/Sprites/IDLE.png"));
	vy = 0.0f;
	gravity = 0.5f;
	jumpPower = -10.0f;
	isGround = false;
	jumpCount = 0;
}

void Player::Update(Input& input) {
	if (input.IsKeyDown(KEY_INPUT_A)) { x -= 5; }
	if (input.IsKeyDown(KEY_INPUT_D)) { x += 5; }

	if (input.IsKeyDownTrigger(KEY_INPUT_SPACE) && jumpCount < 2) {
		vy = -10; jumpCount++;
	}

	vy += 0.5f;
	y += vy;

	
}


void Player::Draw(float camX) {
	int drawX = (int)(x - camX);
	int drawY = (int)y;
	
}