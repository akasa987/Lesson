#pragma once

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();

	virtual void Init() { mIsInit = true; };
	virtual void Load() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Draw3D() = 0;
	virtual void Draw2D() = 0;

protected:
	void LoadModel(const char* path);
	void ReleaseModel();
	int GetModelHandle() { return mModelHandle; }

	HOhara::Vector3 mPos;
	HOhara::Vector3 mRot;

private:
	bool mIsInit;
	int mModelHandle;
};