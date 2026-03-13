#include "option.h"
#include "DxLib.h"
#include "../sceneManager.h"
#include "../title/titleScene.h"
#include "../../Input/Input.h"
#include <cstdio>
#include <cstring>
#include <cmath>

static const char* OPTIONS_PATH = "Data/options.ini";

// 静的メンバの定義
int OptionScene::s_screenW    = 1280;
int OptionScene::s_screenH    = 720;
int OptionScene::s_bgmVolume  = 100;
int OptionScene::s_seVolume   = 100;

const OptionScene::Resolution OptionScene::RES_LIST[4] =
{
    { 800,  600,  "800 x 600"  },
    { 1024, 768,  "1024 x 768" },
    { 1280, 720,  "1280 x 720" },
    { 1920, 1080, "1920 x 1080"},
};

//================
// 設定ファイル
//================

bool OptionScene::LoadFromFile(const char* path)
{
    FILE* f = nullptr;
    fopen_s(&f, path, "r");
    if (!f) return false;

    int w = 0, h = 0, b = 0, s = 0;
    if (fscanf_s(f, "%d %d %d %d", &w, &h, &b, &s) == 4)
    {
        if (w > 0 && h > 0) { s_screenW = w; s_screenH = h; }
        if (b >= 0 && b <= 255) s_bgmVolume = b;
        if (s >= 0 && s <= 255) s_seVolume  = s;
    }
    std::fclose(f);
    return true;
}

bool OptionScene::SaveToFile(const char* path)
{
    FILE* f = nullptr;
    fopen_s(&f, path, "w");
    if (!f) return false;
    std::fprintf(f, "%d %d %d %d\n", s_screenW, s_screenH, s_bgmVolume, s_seVolume);
    std::fclose(f);
    return true;
}

void OptionScene::LoadSettings()
{
    LoadFromFile(OPTIONS_PATH);
}

void OptionScene::SaveSettings()
{
    SaveToFile(OPTIONS_PATH);
}

//================
// Scene interface
//================

void OptionScene::Init()
{
    LoadSettings();

    // 編集用に現在値をコピー
    editBgm = s_bgmVolume;
    editSe  = s_seVolume;

    // 解像度インデックスを現在値に合わせる
    resIndex = 0;
    for (int i = 0; i < RES_COUNT; i++)
    {
        if (RES_LIST[i].w == s_screenW && RES_LIST[i].h == s_screenH)
        {
            resIndex = i;
            break;
        }
    }

    cursor = 0;
}

void OptionScene::Update()
{
    input.Update();

    // 上下でカーソル移動
    if (input.IsKeyDownTrigger(KEY_INPUT_DOWN))
    {
        cursor++;
        if (cursor >= (int)MenuItem::MAX) cursor = 0;
    }
    if (input.IsKeyDownTrigger(KEY_INPUT_UP))
    {
        cursor--;
        if (cursor < 0) cursor = (int)MenuItem::MAX - 1;
    }

    // 左右で値を変更（変えたら即確定・即反映）
    if (input.IsKeyDownTrigger(KEY_INPUT_LEFT))
    {
        switch ((MenuItem)cursor)
        {
        case MenuItem::ScreenSize:
            resIndex = (resIndex - 1 + RES_COUNT) % RES_COUNT;
            s_screenW = RES_LIST[resIndex].w;
            s_screenH = RES_LIST[resIndex].h;
            SaveSettings();
            break;
        case MenuItem::BgmVolume:
            editBgm -= 5;
            if (editBgm < 0) editBgm = 0;
            s_bgmVolume = editBgm;
            SetVolumeSound(s_bgmVolume);
            SaveSettings();
            break;
        case MenuItem::SeVolume:
            editSe -= 5;
            if (editSe < 0) editSe = 0;
            s_seVolume = editSe;
            SetVolumeSoundFile(s_seVolume);
            SaveSettings();
            break;
        default:
            break;
        }
    }
    if (input.IsKeyDownTrigger(KEY_INPUT_RIGHT))
    {
        switch ((MenuItem)cursor)
        {
        case MenuItem::ScreenSize:
            resIndex = (resIndex + 1) % RES_COUNT;
            s_screenW = RES_LIST[resIndex].w;
            s_screenH = RES_LIST[resIndex].h;
            SaveSettings();
            break;
        case MenuItem::BgmVolume:
            editBgm += 5;
            if (editBgm > 255) editBgm = 255;
            s_bgmVolume = editBgm;
            SetVolumeSound(s_bgmVolume);
            SaveSettings();
            break;
        case MenuItem::SeVolume:
            editSe += 5;
            if (editSe > 255) editSe = 255;
            s_seVolume = editSe;
            SetVolumeSoundFile(s_seVolume);
            SaveSettings();
            break;
        default:
            break;
        }
    }

    // Enter で決定（Back 項目）/ ESC：タイトルへ戻る（設定は既に即時保存済み）
    if (input.IsKeyDownTrigger(KEY_INPUT_RETURN))
    {
        if ((MenuItem)cursor == MenuItem::Back)
        {
            SceneManager::ChangeScene(new TitleScene());
            return;
        }
    }

    if (input.IsKeyDownTrigger(KEY_INPUT_ESCAPE))
    {
        SceneManager::ChangeScene(new TitleScene());
        return;
    }

    input.LateUpdate();
}

void OptionScene::Draw()
{
    // 背景
    DrawBox(0, 0, 1280, 720, GetColor(10, 10, 30), TRUE);
    
    // メインボックスのサイズと位置（さらに左寄り）
    const int boxWidth = 500;
    const int boxHeight = 520;
    const int boxX1 = 30;
    const int boxY1 = 100;
    const int boxX2 = boxX1 + boxWidth;
    const int boxY2 = boxY1 + boxHeight;
    
    DrawBox(boxX1, boxY1, boxX2, boxY2, GetColor(20, 20, 60), TRUE);
    DrawBox(boxX1, boxY1, boxX2, boxY2, GetColor(80, 80, 160), FALSE);

    // タイトル（ボックス内で中央揃え）
    const char* titleText = "OPTION";
    int titleWidth = GetDrawStringWidth(titleText, (int)strlen(titleText));
    int boxCenterX = boxX1 + boxWidth / 2;
    DrawString(boxCenterX - titleWidth / 2, boxY1 + 30, titleText, GetColor(255, 255, 100));

    const int startX = boxX1 + 40;
    const int startY = boxY1 + 100;
    const int stepY  = 80;

    // 各メニュー項目
    struct Item { const char* label; };
    char lines[(int)MenuItem::MAX][64] = {};

    // Screen Size
    sprintf_s(lines[0], sizeof(lines[0]),
        "Screen Size  :  < %s >", RES_LIST[resIndex].label);

    // BGM Volume（バー付き）
    int bgmBar = editBgm / 17;  // 0〜15 のバー長さ
    char bgmBuf[20] = {};
    for (int i = 0; i < 15; i++) bgmBuf[i] = (i < bgmBar) ? '|' : '-';
    sprintf_s(lines[1], sizeof(lines[1]),
        "BGM Volume   :  < [%s] %3d >", bgmBuf, editBgm);

    // SE Volume（バー付き）
    int seBar = editSe / 17;
    char seBuf[20] = {};
    for (int i = 0; i < 15; i++) seBuf[i] = (i < seBar) ? '|' : '-';
    sprintf_s(lines[2], sizeof(lines[2]),
        "SE  Volume   :  < [%s] %3d >", seBuf, editSe);

    sprintf_s(lines[3], sizeof(lines[3]), "Back  (Esc / Enter)");

    for (int i = 0; i < (int)MenuItem::MAX; i++)
    {
        int y = startY + i * stepY;
        int color = (i == cursor) ? GetColor(255, 255, 0) : GetColor(200, 200, 200);

        // 選択中はハイライト
        if (i == cursor)
        {
            DrawBox(startX - 20, y - 8, boxX2 - 20, y + 28, GetColor(40, 40, 100), TRUE);
            DrawBox(startX - 20, y - 8, boxX2 - 20, y + 28, GetColor(100, 100, 200), FALSE);
        }

        DrawString(startX, y, lines[i], color);
    }

    // 操作ヒント
    DrawString(startX, boxY2 - 80, "Up/Down: Move cursor   Left/Right: Change value", GetColor(140, 140, 140));
    DrawString(startX, boxY2 - 60, "Enter: Back & Save   Esc: Cancel", GetColor(140, 140, 140));

    // 解像度変更の注意書き
    DrawString(startX, boxY2 - 30, "* Resolution change will be applied after restart.", GetColor(180, 100, 100));
}

void OptionScene::End()
{
}
