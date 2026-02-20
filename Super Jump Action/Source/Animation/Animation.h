#pragma once

/*
Animationクラス　使用方法

【概要】
フレーム番号を管理するAnimation用クラス
DxLibには依存してない

【使い方】
1．アニメ開始
　anim.Start(開始フレーム,終了フレーム,再生速度,ループするか);
例：
　anim.Start(0,5,20,true);
 0～5を20フレーム感覚でループ再生

2．毎フレーム更新
　anim.Update();

3.描画時に現在フレームを取得
　int frame = anim.GetFrame();

4.ループしないアニメの終了確認
　if(anim.IsFinished())
 {
    エフェクトとか消す
 }

 【注意】
 Start()は状態が変わったときだけ呼ばないと
 挙動バグるよ

*/

class Animation
{
public:
    Animation();

    // アニメ開始
    void Start(int startFrame, int endFrame, int speed, bool loop);

    // 毎フレーム呼ぶ
    void Update();

    // 今のフレーム取得
    int GetFrame() const;

    // ループしないアニメが終わったか
    bool IsFinished() const;

private:
    int start;
    int end;
    int current;
    int speed;
    int counter;
    bool loop;
    bool finished;
};