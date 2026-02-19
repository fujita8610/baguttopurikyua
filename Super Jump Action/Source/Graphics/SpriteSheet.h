#pragma once
#include "DxLib.h"
/*
SpriteSheetクラス　使用方法
【概要】
スプライトシート(横に長い画像)を分割して管理するクラス
DxLibのLoadDivGraphを内部で使用している

【使い方】
1．画像を読み込む
　spriteSheet sprite;
　sprite.Load("player.png",横分割数,1コマ幅,1コマ高さ);
例：
　sprite.Load("player.png", 6, 1, 32, 32);
  縦6×横1の32×32の画像に分割される

2.フレーム番号を指定して描画
　DrawGraph(x, y,
            sprite.Get(frameIndex),
            TRUE);
  
  frameIndexは分割した時の使いたい画像ファイルの番号

【フレームの並び】
　0, 1, 2, 3, ~
　横方向に進み、端まで行ったら次の段へ。
*/

class SpriteSheet
{
public:
    SpriteSheet();

    // スプライトシート読み込み＆分割
    bool Load(const char* path,
        int divX,
        int divY,
        int frameW,
        int frameH);

    // フレーム取得
    int Get(int index) const;

    // 総フレーム数取得
    int GetTotal() const;

private:
    int handle[256];  // 最大256フレーム
    int total;
};