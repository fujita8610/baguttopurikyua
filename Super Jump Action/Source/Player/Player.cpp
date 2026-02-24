#include "Player.h"

//マップ関連
#include "../map/map.h"
#include "../map/tileManager/tileManager.h"

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

void Player::Update(Input& input) 
{
	//移動
	if (input.IsKeyDown(KEY_INPUT_A))
	{
		pos.x -= speed;
	}

	if (input.IsKeyDown(KEY_INPUT_D))
	{
		pos.x += speed;
	}

	//ジャンプ
	if (input.IsKeyDownTrigger(KEY_INPUT_SPACE) && jumpCount < 2)
	{
		vy = jumpPower;

		jumpCount++;
	}

	//重力
	vy += gravity;


	// 次のY位置
	float nextY = pos.y;


	//================
	// タイル座標変換
	//================

	float scale = TileManager::GetScale();
	float tileSize = TILE_SIZE * scale;

	// プレイヤーサイズ
	int width = 32;
	int height = 32;


	int leftTile =
		(int)(pos.x / tileSize);

	int rightTile =
		(int)((pos.x + width - 1) / tileSize);

	int bottomTile =
		(int)((nextY + height) / tileSize);


	//================
	// 地面判定
	//================

	if (vy > 0 &&
		(IsWall(leftTile, bottomTile) ||
			IsWall(rightTile, bottomTile)))
	{
		pos.y = bottomTile * tileSize - height;

		vy = 0;

		isGround = true;

		jumpCount = 0;
	}
	else
	{
		pos.y = nextY;

		isGround = false;
	}
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

float Player::GetX() const
{
	return pos.x;
}

float Player::GetY() const
{
	return pos.y;
}