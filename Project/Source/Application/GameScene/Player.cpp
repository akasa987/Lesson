#include "Player.h"

Player::Player()
{
	mPos = HOhara::Vector3(0, 1.0f, 0);
	mRot = HOhara::Vector3::Zero();
	mLookVec = HOhara::Vector3::Forward();
}

Player::~Player()
{
}

void Player::Init()
{
	mGunModelHandle = MV1LoadModel("Data/gun.mv1");
	mGunMat = HOhara::Matrix4x4::Identity();
	mGravity = 0;
}

void Player::Release()
{
	MV1DeleteModel(mGunModelHandle);
}

void Player::Update()
{
	HOhara::Vector3 inputVec = HOhara::Vector3::Zero();
	if (CheckHitKey(KEY_INPUT_W))
	{
		inputVec += HOhara::Vector3(0, 0, 1.0f);
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		inputVec += HOhara::Vector3(0, 0, -1.0f);
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		inputVec += HOhara::Vector3(-1.0f, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		inputVec += HOhara::Vector3(1.0f, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//重力を逆にしてジャンプさせる
		mGravity = 0.5f;
	}
	inputVec.Normalize();

	const int centerX = 640 / 2;
	const int centerY = 480 / 2;

	int mouseX, mouseY;
	// 現在のマウス座標を取得
	GetMousePoint(&mouseX, &mouseY);
	// マウスを中心に固定
	SetMousePoint(centerX, centerY);
	// 中心からどれだけ動いたか計算
	int deltaX = mouseX - centerX;
	int deltaY = mouseY - centerY;

	// マウスの移動量に合わせて、カメラ回転
	mRot.y += deltaX * 0.2f;
	mRot.x += deltaY * 0.2f;
	//一定以上は回転しないように上限値を設定
	if (mRot.x > 80.0f)
	{
		mRot.x = 80.0f;
	}
	if (mRot.x < -80.0f)
	{
		mRot.x = -80.0f;
	}
	//移動ベクトルの回転行列を作成
	HOhara::Matrix4x4 rotMat = HOhara::Matrix4x4::RotateXYZ(HOhara::Vector3(0, mRot.y, 0));
	//移動ベクトルを作成
	inputVec = inputVec.Rotate(rotMat);

	//視点の回転行列を作成
	rotMat = HOhara::Matrix4x4::RotateXYZ(mRot);
	//視点のベクトルを作成
	mLookVec = HOhara::Vector3(0, 0, 1.0f).Rotate(rotMat);

	HOhara::Vector3 moveVec = inputVec * 0.1f;
	HOhara::Matrix4x4 mapMat = HOhara::Matrix4x4::Identity();
	//球とメッシュによる判定
	HOhara::WallSlideSphere(mMapModelHandle, mapMat, mPos, moveVec, 1.0f);
	//座標の適用
	mPos += moveVec;

	mGravity -= 0.01f;
	HOhara::Vector3 rayLookVec = mPos + (HOhara::Vector3::Down() * 100);
	HOhara::RayResult rayResult = HOhara::RayModelCheck(mMapModelHandle, HOhara::Matrix4x4::Identity(), mPos, rayLookVec);
	if (rayResult.isHit && rayResult.distance <= 1.5f && mGravity < 0)
	{
		mGravity = 0;
		mPos.y = rayResult.hitPos.y + 1.5f;
	}

	mPos.y += mGravity;

	//銃の表示位置の行列を設定
	mGunMat = HOhara::Matrix4x4::Scale(HOhara::Vector3(0.01f, 0.01f, 0.01f)) *
		HOhara::Matrix4x4::Translate(HOhara::Vector3(0.2f, -0.1f, 0.2f)) *
		rotMat *
		HOhara::Matrix4x4::Translate(mPos);
}

void Player::CamaraUpdate()
{
	//カメラのニアの設定
	SetCameraNearFar(0.1f, 1000.0f);
	//カメラの設定
	SetCameraPositionAndTarget_UpVecY(mPos, mPos + mLookVec);
}

void Player::Draw3D()
{
	MV1SetMatrix(mGunModelHandle, mGunMat);
	MV1DrawModel(mGunModelHandle);
}

void Player::SetMapModelHandle(int handle)
{
	mMapModelHandle = handle;
}