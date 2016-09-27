#pragma once

#include<string>
#include<map>

class AssetStorage
{
public:
	static AssetStorage& getInstance();
	~AssetStorage();
	void HandleRegister(std::string fileName, std::string key);
	int GetHandle(std::string key);
	void Clear();

private:
	AssetStorage();

private:
	std::map<std::string, int> mAssets;

};
