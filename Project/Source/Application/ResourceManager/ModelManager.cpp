#include "ModelManager.h"

int ModelManager::GetModel(std::string path)
{
	if (IsModel(path))
	{
		return mModelMap[path];
	}
	int modelID = MV1LoadModel(path.c_str());
	mModelMap.insert({ path, modelID });
	return modelID;
}

bool ModelManager::IsModel(std::string path)
{
	auto it = mModelMap.find(path);
	if (it != mModelMap.end())
	{
		// ë∂ç›Ç∑ÇÈ
		return true;
	}
	return false;
}

void ModelManager::Delete(std::string path)
{
	if (!IsModel(path)) return;
	MV1DeleteModel(mModelMap[path]);
	mModelMap.erase(path);
}

void ModelManager::AllDelete()
{
	for (const auto& pair : mModelMap)
	{
		MV1DeleteModel(pair.second);
	}
	mModelMap.clear();
}
