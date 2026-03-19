#include "TutorialBoss.h"
#include "DxLib.h"
#include "../../../map/map.h"
#include "../../../map/tileManager/tileManager.h"

//デバック
#include "../../../GameDebug/GameDebug.h"

TutorialBoss::TutorialBoss(float startX, float startY)
    : BossBase(startX, startY, 3)
{
    idle.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_idle.png", 5, 1, 128, 128);

    flagBlack.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_ability_black.png", 25, 1, 384, 128);
    flagRed.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_ability_red.png", 25, 1, 384, 128);
    flagYellow.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_ability_yellow.png", 25, 1, 384, 128);

    stamp.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_attack_A.png", 21, 1, 384, 128);

    dashStart.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_attack_B_1_start.png", 10, 1, 384, 128);
    dashLoop.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_attack_B_2_loop.png", 5, 1, 384, 128);
    dashEnd.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_attack_B_3_end.png", 7, 1, 384, 128);

    state = State::Idle;
    idleRolled = false;
    idleTimer = 60;
    anim.Start(0, idle.GetTotal() - 1, 10, true);
}

void TutorialBoss::ChangeState(State newState)
{
    state = newState;

    switch (state)
    {
    case State::Wait:
        anim.Start(0, idle.GetTotal() - 1, 10, true);
        break;

    case State::Idle:
        anim.Start(0, idle.GetTotal() - 1, 10, true);
        idleRolled = false;
        idleTimer = 60;
        break;

    case State::FlagBlack:
        anim.Start(0, flagBlack.GetTotal() - 1, 4, false);
        break;

    case State::FlagRed:
        anim.Start(0, flagRed.GetTotal() - 1, 4, false);
        break;

    case State::FlagYellow:
        anim.Start(0, flagYellow.GetTotal() - 1, 4, false);
        break;

    case State::Stamp:
        anim.Start(0, stamp.GetTotal() - 1, 4, false);
        break;

    case State::DashStart:
        anim.Start(0, dashStart.GetTotal() - 1, 4, false);
        break;

    case State::DashLoop:
        anim.Start(0, dashLoop.GetTotal() - 1, 4, true);
        break;

    case State::DashEnd:
        anim.Start(0, dashEnd.GetTotal() - 1, 4, false);
        break;

    default:
        break;
    }
}

void TutorialBoss::Update(const Player& player)
{
    if (invincibleTimer > 0)
        invincibleTimer--;

    if (!isAlive)
    {
        deathTimer++;
        return;
    }

    if (hp <= 0)
    {
        isAlive = false;
        deathTimer = 0;
        return;
    }

    bool stateChanged = false;

    switch (state)
    {

    case State::Idle:
    {
        if (!idleRolled)
        {
            idleTimer--;
            if (idleTimer <= 0)
            {
                idleRolled = true;

                int r = GetRand(2);
                if (r == 0) ChangeState(State::FlagBlack);
                else if (r == 1) ChangeState(State::FlagRed);
                else ChangeState(State::FlagYellow);

                stateChanged = true;
            }
        }
    }
    break;

    case State::Wait:
        waitTimer--;
        if (waitTimer <= 0)
        {
            ChangeState(State::Idle);
            stateChanged = true;
        }
        break;

    case State::FlagBlack:

        if (anim.IsFinished())
        {
            waitTimer = 120;
            ChangeState(State::Wait);
            stateChanged = true;
        }

        break;

    case State::FlagRed:

        if (anim.IsFinished())
        {
            ChangeState(State::Stamp);
            stateChanged = true;
        }

        break;

    case State::FlagYellow:

        if (anim.IsFinished())
        {
            ChangeState(State::DashStart);
            stateChanged = true;
        }

        break;

    case State::Stamp:
    {
        int frame = anim.GetFrame();
        stampAttacking = (frame >= 8 && frame <= 10);

        if (anim.IsFinished())
        {
            ChangeState(State::Idle);
            stateChanged = true;
        }
    }
        break;

    case State::DashStart:

        if (anim.IsFinished())
        {
            ChangeState(State::DashLoop);
            stateChanged = true;
        }

        break;

    case State::DashLoop:
        dashFlashTimer++;

        x += dashSpeed * direction;

        if (x < camXRef)  // ← 左端
        {
            direction *= -1;
            x = camXRef;
            ChangeState(State::DashEnd);
            stateChanged = true;
            break;
        }

        // 右：タイルの壁
        {
            const int actualTileSize = TILE_SIZE * SCALE;
            int checkX = (int)(x + 128) / actualTileSize;
            int checkY = (int)(y + 64) / actualTileSize;

            if (IsWall(checkX, checkY))
            {
                direction *= -1;
                x -= dashSpeed * 2;
                ChangeState(State::DashEnd);
                stateChanged = true;
            }
        }

        break;

    case State::DashEnd:
        dashFlashTimer = 0;

        if (anim.IsFinished())
        {
            ChangeState(State::Idle);
            stateChanged = true;
        }

        break;

    }

    if (!stateChanged)
    anim.Update();

}

void TutorialBoss::Draw(float camX, float camY)
{
    int frame = anim.GetFrame();
    int handle = -1;
    int offsetX = 0;

    switch (state)
    {
    case State::Wait:
        handle = idle.Get(frame);
        break;

    case State::Idle:
        handle = idle.Get(frame);
        break;

    case State::FlagBlack:
        handle = flagBlack.Get(frame);
        offsetX = -128;
        break;

    case State::FlagRed:
        handle = flagRed.Get(frame);
        offsetX = -128;
        break;

    case State::FlagYellow:
        handle = flagYellow.Get(frame);
        offsetX = -128;
        break;

    case State::Stamp:
        handle = stamp.Get(frame);
        offsetX = -128;
        break;

    case State::DashStart:
        handle = dashStart.Get(frame);
        offsetX = -128;
        break;

    case State::DashLoop:
        handle = dashLoop.Get(frame);
        offsetX = -128;
        break;

    case State::DashEnd:
        handle = dashEnd.Get(frame);
        offsetX = -128;
        break;
    }

    int drawX = (int)(x - camX) + offsetX;
    int drawY = (int)(y - camY);

    if (handle == -1) return;

    if (!isAlive)
    {
        float ratio = 1.0f - (float)deathTimer / DEATH_DURATION;
        int bright = (int)(255 * ratio);
        bright = max(0, bright);
        SetDrawBright(bright, bright, bright);

        // 上から消える
        int clipH = (int)(128 * ratio);
        if (clipH <= 0)
        {
            SetDrawBright(255, 255, 255);
            return;  // 完全に消える
        }

        SetDrawArea(0, (int)(y - camY) + (128 - clipH), 1920, 1080);
    }
    else if (state == State::DashLoop)
    {
        // ★ダッシュ中は黄色く点滅
        if (dashFlashTimer % 4 < 2)
            SetDrawBright(255, 255, 0);
    }
    else if (invincibleTimer > 0 && (invincibleTimer % 4 < 2))
    {
        SetDrawBright(255, 0, 0);  // ダメージ時は赤
    }

    if (direction == 1)
        DrawGraph(drawX, drawY, handle, TRUE);
    else
        DrawTurnGraph(drawX, drawY, handle, TRUE);

    SetDrawBright(255, 255, 255);
    SetDrawArea(0, 0, 1920, 1080);

    if (GameDebug::IsDebug())
    {
        // 胴体の当たり判定（赤）
        Rect r = GetRect();
        DrawBox(
            (int)(r.left - camX),
            (int)(r.top - camY),
            (int)(r.right - camX),
            (int)(r.bottom - camY),
            GetColor(255, 0, 0),
            FALSE
        );

        // 頭の当たり判定（青）
        Rect h = GetHeadRect();
        DrawBox(
            (int)(h.left - camX),
            (int)(h.top - camY),
            (int)(h.right - camX),
            (int)(h.bottom - camY),
            GetColor(0, 0, 255),
            FALSE
        );

        if (stampAttacking)
        {
            Rect sa = GetStampAttackRect();
            DrawBox(
                (int)(sa.left - camX),
                (int)(sa.top - camY),
                (int)(sa.right - camX),
                (int)(sa.bottom - camY),
                GetColor(255, 255, 0),  // 黄色
                FALSE
            );
        }

    }
}

Rect TutorialBoss::GetHeadRect() const
{
    Rect r;
    if (direction == -1)  // 右向き
    {
        r.left = x + 25;
        r.right = x + 80;
    }
    else  // 左向き
    {
        r.left = x + 128 - 80;  // x + 48
        r.right = x + 128 - 25;  // x + 103
    }
    r.top = y + 60;
    r.bottom = y + 95;
    return r;
}

Rect TutorialBoss::GetRect() const
{
    Rect r;
    if (direction == -1)  // 右向き
    {
        r.left = x + 25;
        r.right = x + 100;
    }
    else  // 左向き
    {
        r.left = x + 128 - 100;  // x + 28
        r.right = x + 128 - 25;   // x + 103
    }
    r.top = y + 95;
    r.bottom = y + 128;
    return r;
}

Rect TutorialBoss::GetStampAttackRect() const
{
    Rect r;
    if (direction == -1)  // 左向き
    {
        r.left = x - 60;
        r.right = x + 25;
    }
    else  // 右向き
    {
        r.left = x + 100;
        r.right = x + 185;
    }
    r.top = y + 90;
    r.bottom = y + 128;
    return r;
}

void TutorialBoss::TakeDamage(int damage)
{
    if (invincibleTimer > 0) return;
    if (state == State::DashLoop) return;

    BossBase::TakeDamage(damage);

    if (isAlive)
    {
        ChangeState(State::DashStart);
    }
}