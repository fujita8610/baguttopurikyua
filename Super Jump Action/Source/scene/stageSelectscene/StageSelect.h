#pragma once
#include "../scene.h"
#include "../../Input/Input.h"

class StageSelectScene : public Scene
{
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void End() override;

private:
    Input input;

    int cursor = 0;
    static const int STAGE_MAX = 4;

    int inputWait = 10;
    int blinkTimer = 0;
};