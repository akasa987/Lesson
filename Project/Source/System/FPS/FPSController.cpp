#include "FPSController.h"

FPSController::FPSController(int fps)
{
    mStartTime = GetNowCount();
    mCount = 0;
    mFps = 0;
    N = FPS = fps;
}

void FPSController::Init()
{
    SetWaitVSyncFlag(false);
}

bool FPSController::Update()
{
    if (mCount == 0) 
    {
        mStartTime = GetNowCount();
    }
    if (mCount == N) 
    {
        int t = GetNowCount();
        mFps = 1000.f / ((t - mStartTime) / (float)N);
        mCount = 0;
        mStartTime = t;
    }
    mCount++;
    return true;
}

void FPSController::Draw()
{
    DrawFormatString(FPS_X, FPS_Y, GetColor(255, 255, 255), "%.1f", mFps);
}

void FPSController::Wait()
{
    int tookTime = GetNowCount() - mStartTime;      //‚©‚©‚Á‚½ŽžŠÔ
    int waitTime = mCount * 1000 / FPS - tookTime;  //‘Ò‚Â‚×‚«ŽžŠÔ
    if (waitTime > 0) 
    {
        Sleep(waitTime);  //‘Ò‹@
    }
}

