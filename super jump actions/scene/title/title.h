#pragma once
#include "../scene.h"

class TitleScene : public Scene
{
public:

    void Init() override;
    void Update() override;
    void Draw() override;
    void End() override;

private:

    int titleImage;
    int pushKeyFlash;
};
