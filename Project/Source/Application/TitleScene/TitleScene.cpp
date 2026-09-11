#include "TitleScene.h"
#include "../SceneManager/SceneManager.h"
#include "../GameScene/GameScene.h"

void TitleScene::Init()
{
	mTitleTexture = LoadGraph("Data/tree01.png");
}

void TitleScene::Release()
{
	DeleteGraph(mTitleTexture);
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T))
	{
		//sceneêÿÇËë÷Ç¶Çé¿ëï
		SCENE_MGR.ChangeScene(new GameScene());
		return;
	}
}

void TitleScene::CameraUpdate()
{
}

void TitleScene::Draw3D()
{
}

void TitleScene::Draw3DZBuffer()
{
}

void TitleScene::Draw2D()
{
	DrawRectGraph(1280 / 2 - (100 / 2), 720 / 2 - (100 / 2), 0, 0, 256, 256, mTitleTexture, 1);
}
