#include "Application\SceneManager\SceneManager.h"
#include "Application\GameScene\GameScene.h"
#include "Application\PlaneGameScene\PlaneGameScene.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine, int nCmdShow )
{
	//Log.txtを生成しないように設定
	SetOutApplicationLogValidFlag(false);
	//非全画面にセット
	ChangeWindowMode(true);
	//画面サイズ指定
	SetGraphMode(1280, 720, 32);
	//ウインド名
	SetMainWindowText("Game");
	//バックのカラー設定
	SetBackgroundColor(0, 0, 255);

	//初期化に失敗時にエラーを吐かせて終了
	if (DxLib_Init() == 1) { return -1; }

	FPSController fps(60);
	fps.Init();
	SCENE_MGR.Init(new GameScene());

	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		fps.Update();
		//裏画面消す
		ClearDrawScreen();
		//描画先を裏画面に
		SetDrawScreen(DX_SCREEN_BACK);

		SCENE_MGR.Update();
		//fps.Draw();
		//裏画面を表画面にコピー
		ScreenFlip();
		fps.Wait();
	}
	MODEL_MGR.AllDelete();
	SCENE_MGR.Release();

	DxLib_End();

	return 0 ;					// ソフトの終了
}
