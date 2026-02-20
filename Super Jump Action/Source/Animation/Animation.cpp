#include "Animation.h"

Animation::Animation()
{
    start = 0;
    end = 0;
    current = 0;
    speed = 1;
    counter = 0;
    loop = true;
    finished = false;
}

// アニメーション開始
void Animation::Start(int startFrame, int endFrame, int spd, bool lp)
{
    start = startFrame;
    end = endFrame;
    speed = spd;
    loop = lp;

    current = start;
    counter = 0;
    finished = false;
}

void Animation::Update()
{
    if (finished) return;

    counter++;

    if (counter >= speed)
    {
        counter = 0;
        current++;

        if (current > end)
        {
            if (loop)
            {
                current = start;
            }
            else
            {
                current = end;
                finished = true;
            }
        }
    }
}

int Animation::GetFrame() const
{
    return current;
}

bool Animation::IsFinished() const
{
    return finished;
}