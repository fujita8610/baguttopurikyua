#pragma once
#include "DxLib.h"

//入力
#include "../Input/Input.h"
#include "../System/cooldown.h"

//当たり判定
#include "../System/Rect.h"

//アニメーション関連
#include "../Graphics/SpriteSheet.h"
#include "../Animation/Animation.h"

//enemy関連
#include "../Enemy/EnemyBase/EnemyBase.h"


class Player
{
public:
    Player();
    void Update(Input& input);
    void Draw(float camX, float camY);

    float GetX() const;
    float GetY() const;

    //当たり判定
    Rect GetRect() const;

    // 攻撃判定（攻撃中のみ有効な矩形を返す）
    bool IsAttacking() const;
    Rect GetAttackRect() const;

    bool IsJumping() const;
    bool IsAlive() const;
    bool IsDeathAnimationFinished() const;

    //初期位置
    void SetPosition(float x, float y);

    //倍率変数
    void SetScale(float s);

    // 敵との接触判定（上から踏んだか横からぶつかったか判定）
    void CheckEnemyCollision(const Rect& enemyRect, bool& outEnemyStomped);

    // 敵に踏まれてダメージを受ける（踏まれ判定を無視する敵用）
    void TakeDamageFromEnemy();

private:
    void StartDeath();

    //位置座標
    VECTOR pos;
    int speed;
    int image;

    int width;   
    int height;


    // 当たり判定
    int hitWidth;
    int hitHeight;

    float vy;
    float gravity;
    float jumpPower;

    float scale; //倍率

    bool isGround;
    int jumpCount;

    //通常 cpp/.h での宣言用パターン
    Cooldown jumpCooldown;

    // アニメーション関連
    SpriteSheet spriteIdle;   // Idle用
    SpriteSheet spriteRun;    // Run用
    SpriteSheet spriteJump;   // Jump用(上昇)
    SpriteSheet spriteFall;   // Fall用(落下)
    SpriteSheet spriteAttack; // Attack用(横攻撃)
    SpriteSheet spriteDeath;  // Death用
    
    Animation anim;
    
    int idleFrames;
    int runFrames;
    int jumpFrames;
    int fallFrames;
    int attackFrames;
    int deathFrames;
    
    enum class State { Idle, Run, Jump, Fall, Attack, Death } state;
    bool useSpriteSheet;

    // 方向(true = 右向き、false = 左向き)
    bool facingRight;

    // 攻撃関連
    bool attacking;
    int attackTimer;
    bool attackingRight; // 攻撃方向（true = 右、false = 左）

    // 生死状態
    bool alive;
};

