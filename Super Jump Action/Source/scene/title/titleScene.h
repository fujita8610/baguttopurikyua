#pragma once
#include "../scene.h"
#include "../../Input/Input.h"

class TitleScene : public Scene
{

    public:
        void Init() override;
        void Update() override;
        void Draw() override;
        void End() override;

    private:
        Input input;
};