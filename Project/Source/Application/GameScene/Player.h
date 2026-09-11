#pragma once

class Player
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

	//初期化
	void Init();
	//破棄
	void Release();
	// 更新処理
	void Update();
	// カメラ更新処理
	void CamaraUpdate();
	// 3D描画処理
	void Draw3D();

	void SetMapModelHandle(int handle);
private:
	HOhara::Vector3 mPos;
	HOhara::Vector3 mRot;
	HOhara::Vector3 mLookVec;

	int mGunModelHandle;
	HOhara::Matrix4x4 mGunMat;

	float mGravity;
	int mMapModelHandle;
};