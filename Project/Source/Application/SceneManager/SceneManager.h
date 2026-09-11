#pragma once
class SceneBase;

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="sceneBase"></param>
	void Init(SceneBase* sceneBase);

	/// <summary>
	/// 破棄
	/// </summary>
	void Release();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// シーンの切り替え
	/// </summary>
	/// <param name="sceneBase"></param>
	void ChangeScene(SceneBase* sceneBase);

private:
	SceneBase* mSceneBase;

	//シングルトン実装
private:
	SceneManager()
	{
		mSceneBase = nullptr;
	}
public:
	static SceneManager& GetInstance() {
		static SceneManager instance;
		return instance;
	}
};

//長いので省略
#define SCENE_MGR SceneManager::GetInstance()