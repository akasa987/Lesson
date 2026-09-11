#pragma once
class SceneBase
{
public:
	/// <summary>
	/// 初期化関連処理
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// 破棄関連処理
	/// </summary>
	virtual void Release() = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// カメラ更新処理
	/// </summary>
	virtual void CameraUpdate() = 0;
	/// <summary>
	/// 3D描画処理
	/// </summary>
	virtual void Draw3D() = 0;
	/// <summary>
	/// 3DZバッファ描画処理
	/// </summary>
	virtual void Draw3DZBuffer() { };
	/// <summary>
	/// 2D描画処理
	/// </summary>
	virtual void Draw2D() = 0;
private:

};