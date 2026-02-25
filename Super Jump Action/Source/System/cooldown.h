#pragma once

class Cooldown
{
private:

    int timer;      // 現在の残り時間
    int maxTime;    // クールダウン最大値

public:

    Cooldown()
    {
        timer = 0;
        maxTime = 0;
    }

    // 初期化
    void Set(int time)
    {
        maxTime = time;
        timer = 0;
    }

    // 更新（毎フレーム呼ぶ）
    void Update()
    {
        if (timer > 0)
            timer--;
    }

    // 使用可能か
    bool IsReady() const
    {
        return timer == 0;
    }

    // 使用する（クールダウン開始）
    void Start()
    {
        timer = maxTime;
    }

    // 強制リセット
    void Reset()
    {
        timer = 0;
    }

    // 残り時間取得（デバッグ用）
    int GetTimer() const
    {
        return timer;
    }
};