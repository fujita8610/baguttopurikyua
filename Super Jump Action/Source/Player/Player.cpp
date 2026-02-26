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
    //移動
    bool moving = false;
    if (input.IsKeyDown(KEY_INPUT_A))
    {
        pos.x -= speed;
        moving = true;
        facingRight = false; // 左向き
    }

    if (input.IsKeyDown(KEY_INPUT_D))
    {
        pos.x += speed;
        moving = true;
        facingRight = true; // 右向き
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
    float nextY = pos.y + vy;

    //================
    // タイル座標変換
    //================

    float scale = TileManager::GetScale();
    float tileSize = TILE_SIZE * scale;

    // プレイヤーサイズ
    // width, height はメンバで定義済み

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

    //========
    // アニメ状態更新
    //========

    State newState = State::Idle;
    if (!isGround)
    {
        // 空中にいる時は速度で判定
        if (vy < 0)
        {
            newState = State::Jump;  // 上昇中
        }
        else
        {
            newState = State::Fall;  // 落下中
        }
    }
    else if (moving)
    {
        newState = State::Run;
    }
    else
    {
        newState = State::Idle;
    }

    // 状態変化があればアニメーションを再設定
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
                    anim.Start(0, idleFrames - 1, 8, true); // ゆっくり
                }
                break;
            case State::Run:
                if (runFrames > 0)
                {
                    anim.Start(0, runFrames - 1, 4, true);  // 早め
                }
                break;
            case State::Jump:
                if (jumpFrames > 0)
                {
                    anim.Start(0, jumpFrames - 1, 6, false); // ループなし
                }
                break;
            case State::Fall:
                if (fallFrames > 0)
                {
                    anim.Start(0, fallFrames - 1, 6, false); // ループなし
                }
                break;
            }
        }

        anim.Update();
    }
}

void Player::Draw(float camX)
{
    int drawX = (int)(pos.x - camX);
    int drawY = (int)pos.y;


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
            // 向きに応じて反転描画
            if (facingRight)
            {
                DrawGraph(drawX - width, drawY - height - 15, handle, TRUE);
            }
            else
            {
                // 左向き：DrawTurnGraph で左右反転
                DrawTurnGraph(drawX - width, drawY - height - 15, handle, TRUE);
            }
            
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
            drawX + width,
            drawY + height,
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