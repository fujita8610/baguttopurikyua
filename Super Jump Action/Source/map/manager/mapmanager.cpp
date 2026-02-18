#include "MapManager.h"
#include "../map.h"

StageID MapManager::m_CurrentStage;

const char* StageFileName[STAGE_MAX] =
{
    "data/map/stage_tutoreal.csv",
    "data/map/stage1.csv",
    "data/map/stage2.csv",
    "data/map/stage3.csv"
};

void MapManager::Init()
{
    LoadStage(STAGE_1);
}

void MapManager::LoadStage(StageID stage)
{
    m_CurrentStage = stage;

    LoadMapCSV(StageFileName[stage]);
}

void MapManager::Draw()
{
    DrawMap();
}

StageID MapManager::GetCurrentStage()
{
    return m_CurrentStage;
}
