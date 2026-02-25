#pragma once
#include "../scene.h"
#include "../../Player/Player.h"
#include "../../Input/Input.h"

class GameScene : public Scene
{
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void End() override;

private:
    Player player;
    Input input;
};