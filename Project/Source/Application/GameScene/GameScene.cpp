#include "GameScene.h"
#include "Player.h"
#include "Enemy/TestEnemy.h"
#include "../SceneManager/SceneManager.h"
#include "../TitleScene/TitleScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	mMapModelHandle = MODEL_MGR.GetModel("Data/map.mv1");
	int materialNum = MV1GetMaterialNum(mMapModelHandle);
	for (int i = 0; i < materialNum; i++)
	{
		// 環境光
		MV1SetMaterialAmbColor(mMapModelHandle, i, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

		// 拡散光
		MV1SetMaterialDifColor(mMapModelHandle, i, GetColorF(0.75f, 0.75f, 0.75f, 1.0f));

		// スペキュラ
		MV1SetMaterialSpcColor(mMapModelHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
	}
	//モデルの当たり判定用コリジョンを作成
	MV1SetupCollInfo(mMapModelHandle, -1);

	mMapPos = HOhara::Vector3(0, 0, 0);
	mMapRot = HOhara::Vector3(0, 0, 0);
	mMapScale = HOhara::Vector3::One();

	mSkyModelHandle = MV1LoadModel("Data/SkyBox.mv1");
	mSkyPos = HOhara::Vector3(0, 0, 0);
	mSkyRot = HOhara::Vector3(0, 0, 0);
	mSkyScale = HOhara::Vector3::One() * 3;

	//Playerのメモリを確保(インスタンス)
	mp_Player = new Player();
	mp_Player->Init();
	mp_Player->SetMapModelHandle(mMapModelHandle);
	mp_TestEnemy = new TestEnemy();
	mp_TestEnemy->Init();
	mp_TestEnemy->Load();

	mBGMSoundHandle = LoadSoundMem("Data/BGM.wav");
	mSESoundHandle = LoadSoundMem("Data/Se.wav");
	mSE1SoundHandle = DuplicateSoundMem(mSESoundHandle);
	PlaySoundMem(mBGMSoundHandle, DX_PLAYTYPE_LOOP);
}

void GameScene::Release()
{
	MODEL_MGR.Delete("Data/map.mv1");
	MODEL_MGR.Delete("Data/SkyBox.mv1");
	//メモリを解放
	mp_Player->Release();
	delete mp_Player;
	mp_Player = nullptr;
	mp_TestEnemy->Release();
	delete mp_TestEnemy;
	mp_TestEnemy = nullptr;
	StopSoundMem(mBGMSoundHandle);
	StopSoundMem(mSESoundHandle);
	StopSoundMem(mSE1SoundHandle);

	DeleteSoundMem(mBGMSoundHandle);
	DeleteSoundMem(mSESoundHandle);
	DeleteSoundMem(mSE1SoundHandle);
}

void GameScene::Update()
{
	if (CheckHitKey(KEY_INPUT_Y))
	{
		//scene切り替えを実装
		SCENE_MGR.ChangeScene(new TitleScene());
		return;
	}
	mp_Player->Update();
	mp_TestEnemy->Update();
	if (CheckHitKey(KEY_INPUT_P) && !CheckSoundMem(mSE1SoundHandle))
	{
		StopSoundMem(mSE1SoundHandle);
		PlaySoundMem(mSE1SoundHandle, DX_PLAYTYPE_BACK);
	}
}

void GameScene::CameraUpdate()
{
	mp_Player->CamaraUpdate();
}

void GameScene::Draw3D()
{
	MV1SetPosition(mMapModelHandle, mMapPos);
	MV1SetRotationXYZ(mMapModelHandle, mMapRot);
	MV1SetScale(mMapModelHandle, mMapScale);
	MV1DrawModel(mMapModelHandle);

	//ライティングの影響を受けないようにする
	SetUseLighting(false);
	MV1SetPosition(mSkyModelHandle, mSkyPos);
	MV1SetRotationXYZ(mSkyModelHandle, mSkyRot);
	MV1SetScale(mSkyModelHandle, mSkyScale);
	MV1DrawModel(mSkyModelHandle);
	//ライティングを有効にする
	SetUseLighting(true);

	mp_TestEnemy->Draw3D();
}

void GameScene::Draw3DZBuffer()
{
	mp_Player->Draw3D();
}

void GameScene::Draw2D()
{
	mp_TestEnemy->Draw2D();
}
