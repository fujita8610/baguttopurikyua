#pragma once
#include "../../Player/Player.h"

struct Rect
{
	float left;
	float top;
	float right;
	float bottom;
};

class EnemyBase
{
public:
	virtual ~EnemyBase() = default;

	virtual void Update(const Player& player) = 0;
	virtual void Draw(float camX, float camY) = 0;

	virtual Rect GetRect() const;

	virtual bool IsAlive() const { return isAlive; }

	float GetX() const { return x; }
	float GetY() const { return y; }

protected:
	float x = 0.0f;
	float y = 0.0f;

	float scale = 2.0f;

	int width = 32;
	int height = 32;

	int hitWidth = 32;
	int hitHeight = 48;

	int hp = 1;
	bool isAlive = true;
};