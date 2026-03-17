#include "TutorialBoss.h"
#include "DxLib.h"
#include "../../../map/map.h"
#include "../../../map/tileManager/tileManager.h"

//デバック
#include "../../../GameDebug/GameDebug.h"

TutorialBoss::TutorialBoss(float startX, float startY)
    : BossBase(startX, startY, 20)
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

        if (anim.IsFinished())
        {
            ChangeState(State::Idle);
            stateChanged = true;
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

    if (direction == 1)
        DrawGraph(drawX, drawY, handle, TRUE);
    else
        DrawTurnGraph(drawX, drawY, handle, TRUE);

    if (GameDebug::IsDebug())
    {
        Rect r = GetRect();

        DrawBox(
            (int)(r.left - camX),
            (int)(r.top - camY),
            (int)(r.right - camX),
            (int)(r.bottom - camY),
            GetColor(255, 0, 0),
            FALSE
        );
    }
}

Rect TutorialBoss::GetRect() const
{
    Rect r;

    r.left = x;
    r.right = x + 128;
    r.top = y + 32;
    r.bottom = y + 128;

    return r;
}