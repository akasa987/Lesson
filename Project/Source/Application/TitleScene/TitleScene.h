#pragma once
#include "../SceneManager/SceneBase.h"

class TitleScene : public SceneBase
{
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void CameraUpdate() override;
	void Draw3D() override;
	void Draw3DZBuffer() override;
	void Draw2D() override;

private:
	int mTitleTexture;
};