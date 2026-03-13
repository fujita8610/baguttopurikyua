#pragma once
#include "../../../Input/Input.h"
#include "../../../Player/Player.h"

class TutorialManager
{
public:

    void Init(bool enableTutorial);

    void Update(const Player& player, Input& input);

    void Draw();

    bool IsActive() const;

private:

    bool enabled = false;     // チュートリアルマップか
    bool active = false;      // 説明表示中

    int step = 0;

    float triggerX = 0;

};