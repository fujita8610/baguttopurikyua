#include "TutorialBoss.h"
#include "DxLib.h"

//デバック
#include "../../../GameDebug/GameDebug.h"

TutorialBoss::TutorialBoss(float startX, float startY)
    : BossBase(startX, startY, 20)
{
    state = State::Idle;

    idle.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_idle.png", 5, 1, 128, 128);

    flagBlack.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_ability_black.png", 25, 1, 128, 128);
    flagRed.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_ability_red.png", 25, 1, 128, 128);
    flagYellow.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_ability_yellow.png", 25, 1, 128, 128);

    stamp.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_attack_A.png", 21, 1, 128, 128);

    dashStart.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_attack_B_1_start.png", 10, 1, 128, 128);
    dashLoop.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_attack_B_2_loop.png", 5, 1, 128, 128);
    dashEnd.Load("Data/Enemy/Boss_tutorial/Dino Rex/dino_rex_attack_B_3_end.png", 7, 1, 128, 128);

    anim.Start(0, idle.GetTotal() - 1, 10, true);
}

void TutorialBoss::ChangeState(State newState)
{
    state = newState;

    switch (state)
    {
    case State::Idle:
        anim.Start(0, idle.GetTotal() - 1, 10, true);
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
    anim.Update();

    switch (state)
    {

    case State::Idle:
    {
        int r = GetRand(2);

        if (r == 0) ChangeState(State::FlagBlack);
        if (r == 1) ChangeState(State::FlagRed);
        if (r == 2) ChangeState(State::FlagYellow);
    }
    break;

    case State::FlagBlack:

        if (anim.IsFinished())
        {
            waitTimer = 120;
            ChangeState(State::Wait);
        }

        break;

    case State::FlagRed:

        if (anim.IsFinished())
        {
            ChangeState(State::Stamp);
        }

        break;

    case State::FlagYellow:

        if (anim.IsFinished())
        {
            ChangeState(State::DashStart);
        }

        break;

    case State::Wait:

        waitTimer--;

        if (waitTimer <= 0)
        {
            ChangeState(State::Idle);
        }

        break;

    case State::Stamp:

        if (anim.IsFinished())
        {
            ChangeState(State::Idle);
        }

        break;

    case State::DashStart:

        if (anim.IsFinished())
        {
            ChangeState(State::DashLoop);
        }

        break;

    case State::DashLoop:

        x += dashSpeed * direction;

        if (x < 0 || x > 2000)
        {
            direction *= -1;
            ChangeState(State::DashEnd);
        }

        break;

    case State::DashEnd:

        if (anim.IsFinished())
        {
            ChangeState(State::Idle);
        }

        break;

    }
}

void TutorialBoss::Draw(float camX, float camY)
{
    int frame = anim.GetFrame();
    int handle = -1;

    switch (state)
    {

    case State::Idle:
        handle = idle.Get(frame);
        break;

    case State::FlagBlack:
        handle = flagBlack.Get(frame);
        break;

    case State::FlagRed:
        handle = flagRed.Get(frame);
        break;

    case State::FlagYellow:
        handle = flagYellow.Get(frame);
        break;

    case State::Stamp:
        handle = stamp.Get(frame);
        break;

    case State::DashStart:
        handle = dashStart.Get(frame);
        break;

    case State::DashLoop:
        handle = dashLoop.Get(frame);
        break;

    case State::DashEnd:
        handle = dashEnd.Get(frame);
        break;
    }

    int drawX = (int)(x - camX);
    int drawY = (int)(y - camY);

    if (direction == 1)
        DrawTurnGraph(drawX, drawY, handle, TRUE);
    else
        DrawGraph(drawX, drawY, handle, TRUE);

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
    r.top = y;
    r.bottom = y + 128;

    return r;
}