#include "../SceneManager/SceneManager.h"
#include "../PlaneGameScene/PlaneGameScene.h"
#include "../TitleScene/TitleScene.h"

PlaneGameScene::PlaneGameScene()
{
}

PlaneGameScene::~PlaneGameScene()
{
}

void PlaneGameScene::Init()
{
	mMapModelHandle = MV1LoadModel("Data/map.mv1");
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
	mMapPos = HOhara::Vector3(0, 0, 0);
	mMapRot = HOhara::Vector3(0, 0, 0);
	mMapScale = HOhara::Vector3::One();

	mSkyModelHandle = MV1LoadModel("Data/SkyBox.mv1");
	mSkyPos = HOhara::Vector3(0, 0, 0);
	mSkyRot = HOhara::Vector3(0, 0, 0);
	mSkyScale = HOhara::Vector3::One() * 3;

	mPlaneModelHandle = MV1LoadModel("Data/body.mv1");
	mPlaneMat = HOhara::Matrix4x4::RotateY(90) * HOhara::Matrix4x4::Translate(HOhara::Vector3(6.0f, 5.0f, 1.0f));
	mPlaneSpeed = 0;

	mPropellerModelHandle = MV1LoadModel("Data/puropra.mv1");
	mPropellerRotParam = 0;
	mPropellerMat = HOhara::Matrix4x4::Identity();
}

void PlaneGameScene::Release()
{
	MV1DeleteModel(mMapModelHandle);
	MV1DeleteModel(mSkyModelHandle);
	MV1DeleteModel(mPlaneModelHandle);
	MV1DeleteModel(mPropellerModelHandle);
}

void PlaneGameScene::Update()
{
	if (CheckHitKey(KEY_INPUT_Y))
	{
		//scene切り替えを実装
		SCENE_MGR.ChangeScene(new TitleScene());
		return;
	}

	HOhara::Matrix4x4 tmpMat = HOhara::Matrix4x4::Identity();
	if (CheckHitKey(KEY_INPUT_UP))
	{
		tmpMat *= HOhara::Matrix4x4::RotateX(1);
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		tmpMat *= HOhara::Matrix4x4::RotateX(-1);
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		tmpMat *= HOhara::Matrix4x4::RotateZ(1);
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		tmpMat *= HOhara::Matrix4x4::RotateZ(-1);
	}

	mPlaneSpeed -= 0.01f;
	if (mPlaneSpeed <= 0)
	{
		mPlaneSpeed = 0;
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (2.0f >= mPlaneSpeed)
		{
			mPlaneSpeed += 0.03f;
		}
		else
		{
			mPlaneSpeed = 2.0f;
		}
	}
	tmpMat *= HOhara::Matrix4x4::Translate(HOhara::Vector3(0, 0, 0.1f) * mPlaneSpeed);
	mPlaneMat = tmpMat * mPlaneMat;


	mPropellerRotParam += 2.0f;
	if (mPropellerRotParam >= 360.0f) mPropellerRotParam -= 360.0f;
	mPropellerMat = HOhara::Matrix4x4::RotateZ(mPropellerRotParam) * 
		HOhara::Matrix4x4::Translate(HOhara::Vector3(0, 0, 2.8f)) * mPlaneMat;
}

void PlaneGameScene::CameraUpdate()
{
	HOhara::Vector3 camaraPos = HOhara::Vector3(-15.0f, 12.0f, 0);
	//カメラのニアの設定
	SetCameraNearFar(0.1f, 1000.0f);
	//カメラの設定
	SetCameraPositionAndTarget_UpVecY(camaraPos, camaraPos + HOhara::Vector3::Right());
}

void PlaneGameScene::Draw3D()
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

	MV1SetMatrix(mPlaneModelHandle, mPlaneMat);
	MV1DrawModel(mPlaneModelHandle);

	MV1SetMatrix(mPropellerModelHandle, mPropellerMat);
	MV1DrawModel(mPropellerModelHandle);
}

void PlaneGameScene::Draw2D()
{

}
