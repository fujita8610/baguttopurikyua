#pragma once
#include "scene.h"

class SceneManager
{
public:
    static void ChangeScene(Scene* scene);
    static void Update();
    static void Draw();

private:
    static Scene* currentScene;

};