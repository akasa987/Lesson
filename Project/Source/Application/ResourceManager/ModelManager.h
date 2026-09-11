#pragma once

class ModelManager
{
public:
	int GetModel(std::string path);
	bool IsModel(std::string path);
	void Delete(std::string path);
	void AllDelete();

private:
	std::map<std::string, int> mModelMap;

	//ƒVƒ“ƒOƒ‹ƒgƒ“À‘•
private:
	ModelManager()
	{
		mModelMap.clear();
	}
public:
	static ModelManager& GetInstance() {
		static ModelManager instance;
		return instance;
	}
};

//’·‚¢‚Ì‚ÅÈ—ª
#define MODEL_MGR ModelManager::GetInstance()
