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
    state = State::Idle;
    facingRight = true; // 初期状態は右向き

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

    // 少なくとも1つのスプライトが読み込めたら有効化
    if (idleFrames > 0 || runFrames > 0 || jumpFrames > 0 || fallFrames > 0)
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

    if (!isGround)
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
            }
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
        }
        
        if (handle >= 0)
        {

            int spriteW = 96;
            int spriteH = 96;

            int spriteDrawX = drawX - (spriteW - width);
            int spriteDrawY = drawY - (spriteH - height);

            DrawRotaGraph(
                spriteDrawX + 80,
                spriteDrawY + 60,
                scale,      // ← 倍率
                0.0,        // 回転
                handle,
                TRUE,
                !facingRight // 左向きなら反転
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

//倍率変数
void Player:: SetScale(float s)
{
    scale = s;
}