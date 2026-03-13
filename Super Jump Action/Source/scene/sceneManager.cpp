#include "scenemanager.h"

//“ü—Í
#include "../Input/Input.h"

Scene* SceneManager::currentScene = nullptr;

void SceneManager::ChangeScene(Scene* scene)
{
    if (currentScene != nullptr)
    {
        currentScene->End();

        delete currentScene;
    }

  

    currentScene = scene;
    currentScene->Init();

}

void SceneManager::Update()
{
    if (currentScene != nullptr)
    {
        currentScene->Update();
    }
}

void SceneManager::Draw()
{
    if (currentScene != nullptr)
    {
        currentScene->Draw();
    }
}