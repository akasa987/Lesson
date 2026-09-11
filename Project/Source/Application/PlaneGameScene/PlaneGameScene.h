#pragma once
#include "../SceneManager/SceneBase.h"

class PlaneGameScene : public SceneBase
{
public:
	PlaneGameScene();
	~PlaneGameScene();
	void Init() override;
	void Release() override;
	void Update() override;
	void CameraUpdate() override;
	void Draw3D() override;
	void Draw2D() override;

private:

	int mMapModelHandle;
	HOhara::Vector3 mMapPos;
	HOhara::Vector3 mMapRot;
	HOhara::Vector3 mMapScale;

	int mSkyModelHandle;
	HOhara::Vector3 mSkyPos;
	HOhara::Vector3 mSkyRot;
	HOhara::Vector3 mSkyScale;

	int mPlaneModelHandle;
	HOhara::Matrix4x4 mPlaneMat;
	float mPlaneSpeed;

	int mPropellerModelHandle;
	float mPropellerRotParam;
	HOhara::Matrix4x4 mPropellerMat;
};