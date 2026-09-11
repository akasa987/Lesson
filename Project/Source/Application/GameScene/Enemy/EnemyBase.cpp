#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
	mPos = HOhara::Vector3::Zero();
	mRot = HOhara::Vector3::Zero();
	mIsInit = false;
	mModelHandle = -1;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::LoadModel(const char* path)
{
	if (mModelHandle == -1)
	{
		mModelHandle = MV1LoadModel(path);
	}
}

void EnemyBase::ReleaseModel()
{
	if (mModelHandle != -1)
	{
		MV1DeleteModel(mModelHandle);
		mModelHandle = -1;
	}
}
