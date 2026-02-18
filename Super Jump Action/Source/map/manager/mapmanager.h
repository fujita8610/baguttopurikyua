#pragma once

enum StageID
{
    //マップ
    STAGE_tutoreal,
    STAGE_1,
    STAGE_2,
    STAGE_3,

    //追加可能


    //マップの母数
    STAGE_MAX
};

class MapManager
{
public:

    static void Init();

    static void LoadStage(StageID stage);

    static void Draw();

    static StageID GetCurrentStage();

private:

    static StageID m_CurrentStage;
};
