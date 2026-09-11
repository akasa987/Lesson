#pragma once

class FPSController
{
public:
    FPSController(int fps = 60);

    void Init();
    bool Update();
    void Draw();
    void Wait();

private:
    int mStartTime;      //測定開始時刻
    int mCount;          //カウンタ
    float mFps;          //fps
    int N = 60;  //平均を取るサンプル数
    int FPS = 60;  //設定したFPS
    static const int FPS_X = 0;
    static const int FPS_Y = 20;
};