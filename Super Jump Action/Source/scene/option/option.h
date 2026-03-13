#pragma once
#include "../scene.h"
#include "../../Input/Input.h"

class OptionScene : public Scene
{
public:
    void Init()   override;
    void Update() override;
    void Draw()   override;
    void End()    override;

    // 設定値の取得（他のシーンから音量などを参照する用途）
    static int GetBgmVolume() { return s_bgmVolume; }
    static int GetSeVolume()  { return s_seVolume; }
    static void GetScreenSize(int& w, int& h) { w = s_screenW; h = s_screenH; }

    // 設定の保存・読み込み（Main などの起動時に呼ぶ）
    static void LoadSettings();
    static void SaveSettings();

private:
    Input input;

    // メニュー項目
    enum class MenuItem
    {
        ScreenSize = 0,
        BgmVolume,
        SeVolume,
        Back,
        MAX
    };

    int cursor = 0;

    //タイマー
    int blinkTimer = 0;

    // 解像度リスト
    struct Resolution { int w; int h; const char* label; };
    static const Resolution RES_LIST[4];
    static const int RES_COUNT = 4;
    int resIndex = 0;

    // 編集中の音量（確定前の仮値）
    int editBgm = 100;
    int editSe  = 100;

    // 確定済み設定値
    static int s_screenW;
    static int s_screenH;
    static int s_bgmVolume;
    static int s_seVolume;

    // 内部ユーティリティ
    static bool LoadFromFile(const char* path);
    static bool SaveToFile(const char* path);
};
