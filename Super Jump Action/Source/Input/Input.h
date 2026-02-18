#pragma once
#include "DxLib.h"

class Input {
    char prevKey[256];   // 前フレームのキー状態
    char currKey[256];   // 今フレームのキー状態
public:
    Input() { for (int i = 0; i < 256; i++) { prevKey[i] = 0; currKey[i] = 0; } }

    // フレーム開始時に現在キーを取得
    void Update() {
        GetHitKeyStateAll(currKey);
    }

    // フレーム終了時に現在キーを前フレームへコピー
    void LateUpdate() {
        for (int i = 0; i < 256; i++) prevKey[i] = currKey[i];
    }

    // 押されているか（今フレーム）
    bool IsKeyDown(int key) {
        return currKey[key];
    }

    // 押した瞬間だけ（今フレームは押されていて前フレームは押されていない）
    bool IsKeyDownTrigger(int key) {
        return currKey[key] && !prevKey[key];
    }
};
