#pragma once

//システム関連
#include "../System/cooldown.h"


class GameDebug
{
public:

    static void Update();

    static bool IsDebug();

private:

    static bool debug;
    static Cooldown toggleCooldown;
};