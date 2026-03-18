#include "mapmanager.h"
#include "../map.h"

#include "DxLib.h"

StageID MapManager::m_CurrentStage;


//CSV“Ç‚İ‚İêŠ
const char* StageFileName[STAGE_MAX] =
{
    "data/map/CSV/stage_tutoreal.csv",
    "data/map/CSV/stage1.csv",
    "data/map/CSV/stage2.csv",
    "data/map/CSV/stage3.csv"
};

void MapManager::Init(StageID stage)
{
    LoadStage(stage);
}

void MapManager::LoadStage(StageID stage)
{
    m_CurrentStage = stage;

    if (!LoadMapCSV(StageFileName[stage]))
    {
        printfDx("CSV Load Error: %s\n", StageFileName[stage]);
    }
}

void MapManager::Draw(float camX, float camY)
{
    DrawMap(camX,camY);
}

StageID MapManager::GetCurrentStage()
{
    return m_CurrentStage;
}
