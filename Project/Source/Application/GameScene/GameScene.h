#pragma once
#include "../SceneManager/SceneBase.h"
class Player;
class EnemyBase;

class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
	void Init() override;
	void Release() override;
	void Update() override;
	void CameraUpdate() override;
	void Draw3D() override;
	void Draw3DZBuffer() override;
	void Draw2D() override;

private:

	Player* mp_Player;
	EnemyBase* mp_TestEnemy;

	int mMapModelHandle;
	HOhara::Vector3 mMapPos;
	HOhara::Vector3 mMapRot;
	HOhara::Vector3 mMapScale;

	int mSkyModelHandle;
	HOhara::Vector3 mSkyPos;
	HOhara::Vector3 mSkyRot;
	HOhara::Vector3 mSkyScale;

	HOhara::Vector3 mPlayerPos;
	HOhara::Vector3 mPlayerLookVec;
	HOhara::Vector3 mPlayerRot;

	int mBGMSoundHandle;
	int mSESoundHandle;
	int mSE1SoundHandle;
};