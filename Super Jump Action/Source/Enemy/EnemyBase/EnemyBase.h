#pragma once

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

	virtual void Update() = 0;
	virtual void Draw(float camX, float camY) = 0;

	virtual Rect GetRect() const = 0;

	virtual bool IsAlive() const { return isAlive; }

protected:
	float x = 0.0f;
	float y = 0.0f;

	int hp = 1;
	bool isAlive = true;
};