#include "Player.h"

//マップ関連
#include "../map/map.h"
#include "../map/tileManager/tileManager.h"

Player::Player()
{
    pos.x = 100;
    pos.y = 300;
    speed = 5;
    image = -1;
    vy = 0.0f;
    gravity = 0.5f;
    jumpPower = -10.0f;
    isGround = false;
    jumpCount = 0;

    useSpriteSheet = false;
    totalFrames = 0;
    state = State::Idle;

    // スプライトシートを試して読み込む（失敗したら従来の単一画像にフォールバック）
    // divX は仮の分割数（横フレーム数）。必要に応じて調整してください。
    const char* sheetPath = "Data/Player/Sprites/IDLE.png";
    const int divX = 4;
    const int divY = 1;

    if (sprite.Load(sheetPath, divX, divY, width, height))
    {
        totalFrames = sprite.GetTotal();
        if (totalFrames > 0)
        {
            useSpriteSheet = true;
            // 全フレームをアニメーション対象にして開始（速度は状態毎に切替える）
            anim.Start(0, totalFrames - 1, 8, true);
        }
    }

    if (!useSpriteSheet)
    {
        // フォールバック：既存の単一画像読み込み
        image = LoadGraph(TEXT("Data/Player/Sprites/IDLE.png"));
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
    }

    if (input.IsKeyDown(KEY_INPUT_D))
    {
        pos.x += speed;
        moving = true;
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
        newState = State::Jump;
    }
    else if (moving)
    {
        newState = State::Run;
    }
    else
    {
        newState = State::Idle;
    }

    // 状態変化があればアニメーションを再設定（ここでは全フレーム範囲を使うが速度だけ変える）
    if (useSpriteSheet)
    {
        if (newState != state)
        {
            state = newState;
            switch (state)
            {
            case State::Idle:
                anim.Start(0, totalFrames - 1, 12, true); // ゆっくり
                break;
            case State::Run:
                anim.Start(0, totalFrames - 1, 6, true);  // 早め
                break;
            case State::Jump:
                anim.Start(0, totalFrames - 1, 10, true); // 中速
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

    if (useSpriteSheet)
    {
        int frame = anim.GetFrame();
        int handle = sprite.Get(frame);
        if (handle >= 0)
        {
            DrawGraph(drawX, drawY, handle, TRUE);
            // 座標表示（スプライト描画の後に画面左上へ表示）
            DrawFormatString(10, 10, GetColor(255, 255, 255), TEXT("X:%d Y:%d"), (int)pos.x, (int)pos.y);
            return;
        }
    }

    if (image >= 0)
    {
        DrawGraph(drawX, drawY, image, TRUE);
    }

    // 座標表示（フォールバック時も表示）
    DrawFormatString(10, 10, GetColor(255, 255, 255), TEXT("X:%d Y:%d"), (int)pos.x, (int)pos.y);
}

void Player::SetPosition(float x, float y)
{
    pos.x = x;
    pos.y = y;
}

float Player::GetX() const
{
	return pos.x;
}

float Player::GetY() const
{
	return pos.y;
}