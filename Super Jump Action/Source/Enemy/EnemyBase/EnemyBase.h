#pragma once
#include "../../Player/Player.h"
#include "../../System/Rect.h"

class Player;

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
	int GetWidth() const { return hitWidth; }
	int GetHeight() const { return hitHeight; }

	// 踏まれ判定を無視するかどうか（true = 踏んでもダメージなし、横からの接触で死ぬ）
	virtual bool IsInvulnerableToStomp() const { return false; }

	void TakeDamage(int damage)
	{
		if (!isAlive) return;
		hp -= damage;
		if (hp <= 0)
		{
			hp = 0;
			isAlive = false;
		}
	}

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