#pragma once
#include "../scene.h"


//プレイヤー関連
#include "../../Player/Player.h"
#include "../../Input/Input.h"
#include "../../Camera/Camera.h"

//Enemy関連
#include "../../Enemy/EnemyManager/EnemyManager.h"
#include "../../Enemy/MushroomReg/MushroomReg.h"
#include "../../Enemy/MushroomSpike/MushroomSpike.h"

//BOSS関連
#include "../gameScene/BossBattle/BossBattle.h"
#include "../../Enemy/BossEnemy/tutorialBoss/tutorialBoss.h"

//シーン関連
#include "../../GameDebug/GameDebug.h"


class GameScene : public Scene
{
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void End() override;

private:
    //cpp宣言用

    Player player;
    Input input;
    EnemyManager enemyManager;
    BossBattleManager bossBattle;
    TutorialBoss* boss = nullptr;

    //camera座標
    float cameraX = 0;
    float cameraY = 0;

    //ボス戦移行
    float bossTriggerX = 0;
    float bossTriggerY = 0;

  
};