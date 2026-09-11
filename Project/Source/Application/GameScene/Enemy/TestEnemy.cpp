#include "TestEnemy.h"

TestEnemy::TestEnemy()
{
	mHP = 0;
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Init()
{
	EnemyBase::Init();
	mHP = 100;
	mPos = HOhara::Vector3(0, 1, 5.0f);
}

void TestEnemy::Load()
{
	LoadModel("Data/chara.mv1");
}

void TestEnemy::Release()
{
	ReleaseModel();
}

void TestEnemy::Update()
{
	mPos += HOhara::Vector3::Forward() * 0.005f;
}

void TestEnemy::Draw3D()
{
	int modelHandle = GetModelHandle();
	MV1SetPosition(modelHandle, mPos);
	MV1SetRotationXYZ(modelHandle, mRot);
	MV1SetScale(modelHandle, HOhara::Vector3::One());
	MV1DrawModel(modelHandle);
}

void TestEnemy::Draw2D()
{
}

void TestEnemy::Damage(int damage)
{
	mHP -= damage;
}

void TestEnemy::Damage()
{
	mHP -= 5;
}
