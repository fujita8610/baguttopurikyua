#pragma once

//システム関連
#include "../System/cooldown.h"

class Input;

class GameDebug
{
public:

    static void Update(Input& input);

    static bool IsDebug();

private:

    static bool debug;
    static Cooldown toggleCooldown;
};