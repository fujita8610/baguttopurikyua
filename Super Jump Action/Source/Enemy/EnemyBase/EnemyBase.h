#pragma once

class EnemyBase
{
public:
	virtual ~EnemyBase() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool IsAlive() const { return isAlive; }

protected:
	float x = 0.0f;
	float y = 0.0f;

	int hp = 1;
	bool isAlive = true;
};