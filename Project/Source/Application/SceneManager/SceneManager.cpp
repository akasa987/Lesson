#include "SceneManager.h"
#include "SceneBase.h"

void SceneManager::Init(SceneBase* sceneBase)
{
	mSceneBase = sceneBase;
	mSceneBase->Init();
}

void SceneManager::Release()
{
	if (mSceneBase != nullptr)
	{
		mSceneBase->Release();
		HOhara::SafeDelete(mSceneBase);
	}
}

void SceneManager::Update()
{
	if (mSceneBase != nullptr)
	{
		mSceneBase->Update();
		mSceneBase->CameraUpdate();
		mSceneBase->Draw3D();
		//Zバッファの有効
		SetUseZBufferFlag(true);
		ClearDrawScreenZBuffer();
		mSceneBase->Draw3DZBuffer();
		//Zバッファの無効
		SetUseZBufferFlag(false);
		mSceneBase->Draw2D();
	}
}

void SceneManager::ChangeScene(SceneBase* sceneBase)
{
	mSceneBase->Release();
	HOhara::SafeDelete(mSceneBase);
	mSceneBase = sceneBase;
	mSceneBase->Init();
}