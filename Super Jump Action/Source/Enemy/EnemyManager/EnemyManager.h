#pragma once
#include <vector>
#include <memory>

class EnemyBase;

class EnemyManager
{
public:
	void Update();
	void Draw();

	void AddEnemy(std::unique_ptr<EnemyBase> enemy);

private:
	std::vector<std::unique_ptr<EnemyBase>> enemies;
};