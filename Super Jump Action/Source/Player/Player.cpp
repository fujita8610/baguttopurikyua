#include "Player.h"

//Debug表示
#include "../GameDebug/GameDebug.h"

//マップ関連
#include "../map/map.h"
#include "../map/tileManager/tileManager.h"

Player::Player()
{
    pos.x = 5;
    pos.y = 150;
    speed = 3;
    image = -1;
    vy = 0.0f;
    gravity = 0.5f;
    jumpPower = -10.0f;
    isGround = false;
    jumpCount = 0;

    scale = 2.0f;
    width = 32;
    height = 32;

    hitWidth = 32;
    hitHeight = 48;

    useSpriteSheet = false;
    idleFrames = 0;
    runFrames = 0;
    jumpFrames = 0;
    fallFrames = 0;
    attackFrames = 0;
    deathFrames = 0;
    state = State::Idle;
    facingRight = true; // 初期状態は右向き

    attacking = false;
    attackTimer = 0;
    attackingRight = true; // 攻撃方向も初期状態は右

    alive = true; // 初期状態は生存

    // IDLE スプライトシート読み込み
    if (spriteIdle.Load("Data/Player/Sprites/IDLE.png", 10, 1, 96, 96))
    {
        idleFrames = spriteIdle.GetTotal();
    }

    // RUN スプライトシート読み込み
    if (spriteRun.Load("Data/Player/Sprites/RUN.png", 8, 1, 96, 96))
    {
        runFrames = spriteRun.GetTotal();
    }

    // JUMP スプライトシート読み込み(上昇)
    if (spriteJump.Load("Data/Player/Sprites/JUMP.png", 3, 1, 96, 96))
    {
        jumpFrames = spriteJump.GetTotal();
    }

    // FALL スプライトシート読み込み(落下)
    if (spriteFall.Load("Data/Player/Sprites/JUMP-FALL.png", 3, 1, 96, 96))
    {
        fallFrames = spriteFall.GetTotal();
    }

    // AIR ATTACK スプライトシート読み込み(横攻撃)
    if (spriteAttack.Load("Data/Player/Sprites/AIR ATTACK.png", 6, 1, 96, 96))
    {
        attackFrames = spriteAttack.GetTotal();
    }

    // DEATH スプライトシート読み込み
    if (spriteDeath.Load("Data/Player/Sprites/DEATH.png", 9, 1, 96, 96))
    {
        deathFrames = spriteDeath.GetTotal();
    }

    // 少なくとも1つのスプライトが読み込めたら有効化
    if (idleFrames > 0 || runFrames > 0 || jumpFrames > 0 || fallFrames > 0 || attackFrames > 0 || deathFrames > 0)
    {
        useSpriteSheet = true;
        // 初期状態は Idle
        if (idleFrames > 0)
        {
            anim.Start(0, idleFrames - 1, 8, true);
        }
    }
}

void Player::Update(Input& input)
{
    if (!alive)
    {
        if (useSpriteSheet && state == State::Death)
        {
            anim.Update();
        }
        return;
    }

    bool moving = false;

    // 入力
    bool pressingLeft = input.IsKeyDown(KEY_INPUT_A);
    bool pressingRight = input.IsKeyDown(KEY_INPUT_D);

    if (input.IsKeyDownTrigger(KEY_INPUT_A))
    {
        facingRight = false;
    }

    if (input.IsKeyDownTrigger(KEY_INPUT_D))
    {
        facingRight = true;
    }

    //================
    // 左右矢印キーで横攻撃
    //================

    if (!attacking)
    {
        if (input.IsKeyDownTrigger(KEY_INPUT_LEFT))
        {
            attacking = true;
            attackTimer = 0;
            attackingRight = false;  // 攻撃方向は左矢印キーの方向
        }
        else if (input.IsKeyDownTrigger(KEY_INPUT_RIGHT))
        {
            attacking = true;
            attackTimer = 0;
            attackingRight = true;   // 攻撃方向は右矢印キーの方向
        }
    }

    // 攻撃タイマー更新
    if (attacking)
    {
        attackTimer++;
    }

    //================
    // 移動予定座標
    //================

    float nextX = pos.x;

    if (pressingLeft && !pressingRight)
    {
        nextX -= speed;
        moving = true;
        facingRight = false;
    }
    else if (pressingRight && !pressingLeft)
    {
        nextX += speed;
        moving = true;
        facingRight = true;
    }
    else if (pressingLeft && pressingRight)
    {
        if (facingRight)
        {
            nextX += speed;
        }
        else
        {
            nextX -= speed;
        }
        moving = true;
    }

    //================
    // ジャンプ
    //================

    if (input.IsKeyDownTrigger(KEY_INPUT_SPACE) && jumpCount < 2)
    {
        vy = jumpPower;
        jumpCount++;
    }

    //================
    // 重力
    //================

    vy += gravity;

    float nextY = pos.y + vy;

    //================
    // タイルサイズ
    //================

    float scale = TileManager::GetScale();
    float tileSize = TILE_SIZE * scale;

    //================
    // 地面判定
    //================

    int leftTile = (int)(pos.x / tileSize);
    int rightTile = (int)((pos.x + hitWidth - 1) / tileSize);
    int bottomTile = (int)((nextY + hitHeight) / tileSize);

    if (vy > 0 &&
        (IsWall(leftTile, bottomTile) ||
            IsWall(rightTile, bottomTile)))
    {
        pos.y = bottomTile * tileSize - hitHeight;
        vy = 0;
        isGround = true;
        jumpCount = 0;
    }
    else
    {
        pos.y = nextY;
        isGround = false;
    }

    //================
    // 壁判定
    //================

    leftTile = (int)(nextX / tileSize);
    rightTile = (int)((nextX + hitWidth - 1) / tileSize);

    int topTile = (int)(pos.y / tileSize);
    bottomTile = (int)((pos.y + hitHeight - 1) / tileSize);

    if (!IsWall(leftTile, topTile) &&
        !IsWall(leftTile, bottomTile) &&
        !IsWall(rightTile, topTile) &&
        !IsWall(rightTile, bottomTile))
    {
        pos.x = nextX;
    }

    //================
    // アニメーション状態
    //================

    State newState = State::Idle;

    if (attacking)
    {
        newState = State::Attack;
    }
    else if (!isGround)
    {
        if (vy < 0)
        {
            newState = State::Jump;
        }
        else
        {
            newState = State::Fall;
        }
    }
    else if (moving)
    {
        newState = State::Run;
    }

    //================
    // アニメーション更新
    //================

    if (useSpriteSheet)
    {
        if (newState != state)
        {
            state = newState;

            switch (state)
            {
            case State::Idle:
                if (idleFrames > 0)
                {
                    anim.Start(0, idleFrames - 1, 8, true);
                }
                break;

            case State::Run:
                if (runFrames > 0)
                {
                    anim.Start(0, runFrames - 1, 4, true);
                }
                break;

            case State::Jump:
                if (jumpFrames > 0)
                {
                    anim.Start(0, jumpFrames - 1, 6, false);
                }
                break;

            case State::Fall:
                if (fallFrames > 0)
                {
                    anim.Start(0, fallFrames - 1, 6, false);
                }
                break;

            case State::Attack:
                if (attackFrames > 0)
                {
                    anim.Start(0, attackFrames - 1, 4, false);
                }
                break;

            case State::Death:
                if (deathFrames > 0)
                {
                    anim.Start(0, deathFrames - 1, 5, false);
                }
                break;
            }
        }

        // 攻撃アニメーションが終わったら攻撃終了
        if (attacking && anim.IsFinished())
        {
            attacking = false;
            attackTimer = 0;
        }

        anim.Update();
    }
}
void Player::Draw(float camX,float camY)
{
    int drawX = (int)(pos.x - camX);
    int drawY = (int)(pos.y - camY);

    //アニメーション
    if (useSpriteSheet)
    {
        int frame = anim.GetFrame();
        int handle = -1;
        
        // 現在の状態に応じて適切なスプライトシートから取得
        switch (state)
        {
        case State::Idle:
            if (idleFrames > 0)
                handle = spriteIdle.Get(frame);
            break;
        case State::Run:
            if (runFrames > 0)
                handle = spriteRun.Get(frame);
            break;
        case State::Jump:
            if (jumpFrames > 0)
                handle = spriteJump.Get(frame);
            break;
        case State::Fall:
            if (fallFrames > 0)
                handle = spriteFall.Get(frame);
            break;
        case State::Attack:
            if (attackFrames > 0)
                handle = spriteAttack.Get(frame);
            break;
        case State::Death:
            if (deathFrames > 0)
                handle = spriteDeath.Get(frame);
            break;
        }
        
        if (handle >= 0)
        {

            int spriteW = 96;
            int spriteH = 96;

            int spriteDrawX = drawX - (spriteW - width);
            int spriteDrawY = drawY - (spriteH - height);

            // 攻撃状態の場合はattackingRightを基準に反転、それ以外はfacingRightを基準に反転
            bool shouldFlip = (state == State::Attack) ? !attackingRight : !facingRight;

            DrawRotaGraph(
                spriteDrawX + 80,
                spriteDrawY + 60,
                scale,      // ← 倍率
                0.0,        // 回転
                handle,
                TRUE,
                shouldFlip   // 左向きなら反転
            );

            
            // 座標表示（スプライト描画の後に画面左上へ表示）
            DrawFormatString(10, 10, GetColor(255, 255, 255), TEXT("X:%d Y:%d"), (int)pos.x, (int)pos.y);
        }
    }

    if (image >= 0)
    {
        if (facingRight)
        {
            DrawGraph(drawX, drawY, image, TRUE);
        }
        else
        {
            DrawTurnGraph(drawX, drawY, image, TRUE);
        }
    }

    // デバッグ表示
    if (GameDebug::IsDebug())
    {
        //当たり判定の表示
        DrawBox(
            drawX,
            drawY,
            drawX + hitWidth,
            drawY + hitHeight,
            GetColor(255, 0, 0),
            FALSE);

        // 攻撃判定の表示
        if (attacking)
        {
            Rect atkRect = GetAttackRect();
            DrawBox(
                (int)(atkRect.left - camX),
                (int)(atkRect.top - camY),
                (int)(atkRect.right - camX),
                (int)(atkRect.bottom - camY),
                GetColor(255, 255, 0),
                FALSE);
        }

        // 座標表示（フォールバック時も表示）
        DrawFormatString(10, 10, GetColor(255, 255, 255), TEXT("X:%d Y:%d"), (int)pos.x, (int)pos.y);
    }

 
}

void Player::SetPosition(float x, float y)
{
    float scale = TileManager::GetScale();
    float tileSize = TILE_SIZE * scale;

    pos.x = x * tileSize;
    pos.y = y * tileSize;
}

float Player::GetX() const
{
	return pos.x;
}

float Player::GetY() const
{
	return pos.y;
}   

Rect Player::GetRect() const
{
    Rect r;

    r.left = pos.x;
    r.top = pos.y;
    r.right = pos.x + hitWidth;
    r.bottom = pos.y + hitHeight;

    return r;
}

bool Player::IsJumping() const
{
    return !isGround;
}

bool Player::IsAttacking() const
{
    return attacking;
}

Rect Player::GetAttackRect() const
{
    Rect r = {};
    if (!attacking) return r;

    const float attackWidth = 40.0f;
    const float attackHeight = 40.0f;

    if (attackingRight)
    {
        r.left = pos.x + hitWidth;
        r.top = pos.y + (hitHeight - attackHeight) / 2.0f;
        r.right = r.left + attackWidth;
        r.bottom = r.top + attackHeight;
    }
    else
    {
        r.right = pos.x;
        r.top = pos.y + (hitHeight - attackHeight) / 2.0f;
        r.left = r.right - attackWidth;
        r.bottom = r.top + attackHeight;
    }

    return r;
}

//倍率変数
void Player:: SetScale(float s)
{
    scale = s;
}

bool Player::IsAlive() const
{
    return alive;
}

bool Player::IsDeathAnimationFinished() const
{
    return !alive && state == State::Death && anim.IsFinished();
}

void Player::StartDeath()
{
    if (!alive) return;

    alive = false;
    attacking = false;
    attackTimer = 0;
    vy = 0.0f;
    state = State::Death;

    if (useSpriteSheet && deathFrames > 0)
    {
        anim.Start(0, deathFrames - 1, 5, false);
    }
}

void Player::TakeDamageFromEnemy()
{
    StartDeath();
}

void Player::CheckEnemyCollision(const Rect& enemyRect, bool& outEnemyStomped)
{
    if (!alive) return;

    Rect playerRect = GetRect();

    // プレイヤーと敵が接触しているか
    if (playerRect.right < enemyRect.left || 
        playerRect.left > enemyRect.right ||
        playerRect.bottom < enemyRect.top || 
        playerRect.top > enemyRect.bottom)
    {
        outEnemyStomped = false;
        return;
    }

    // 上から踏んだかどうか判定
    // プレイヤーの前フレームのY座標より敵の上の辺が下にあり、
    // 現在のプレイヤーのY座標が敵の上の辺より上の場合、上から踏んだと判定
    float overlap = playerRect.bottom - enemyRect.top;
    float sideOverlap = (playerRect.right < enemyRect.right ? 
                         playerRect.right - enemyRect.left : 
                         enemyRect.right - playerRect.left);

    // 上からの踏みつけ判定（上下の重なりが左右の重なりより大きい、かつ下からの接触ではない）
    if (overlap > 0 && overlap < sideOverlap && vy >= 0 && playerRect.bottom >= enemyRect.top)
    {
        // 上から踏んだ
        outEnemyStomped = true;
        // ジャンプさせる
        vy = jumpPower;
        jumpCount = 0;
    }
    else
    {
        // 横からぶつかった → 死亡
        outEnemyStomped = false;
        StartDeath();
    }
}