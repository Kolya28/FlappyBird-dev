#pragma once
#include "pch.h"
class AssetsManager
{
public:
	AssetsManager() {}
	~AssetsManager() {}

	template<class T>
	T& load(const std::string& name, const fs::path& path)
	{
		auto it = assets.find(name);
		if (it != assets.end())
			return *((T*)it->second);

		T* asset = new T;
		asset->loadFromFile(path.string());

		assets.emplace(name, (void*)asset);

		return *asset;
	}

	template<class T>
	T& get(const std::string& name)
	{
		auto it = assets.find(name);
		if (it == assets.end())
			throw std::exception(("can't get " + name + " from assets").c_str());

		return *((T*)it->second);
	}

	void clean(const std::string& name)
	{
		auto it = assets.find(name);
		if (it == assets.end())
			throw std::exception(("can't clean " + name + " from assets").c_str());

		
		delete it->second;
		assets.erase(it);
	}

	void cleanup()
	{
		std::string err;
		for (auto p : assets)
		{
			err += p.first + "\n";
			delete p.second;
		}

		if(!err.empty())
			std::cerr << "didn't clean\n" << err << std::endl;
	}
private:
	std::map<std::string, void*> assets;
};

//template<class T>
//T& AssetsManager::load(const std::string& name, const fs::path& path)
//{
//	auto it = assets.find(name);
//	if (it != assets.end())
//		return *((T*)it->second);
//
//	T* asset = new T;
//	asset->loadFromFile(path.string());
//
//	assets.insert(std::make_pair(name, (void*)asset));
//
//	return *asset;
//}
//
//template<class T>
//T& AssetsManager::get(const std::string& name)
//{
//	auto it = assets.find(name);
//	if (it == assets.end())
//		throw std::exception("can't get " + name + " from assets");
//
//	return *((T*)it->second);
//}
//
//void AssetsManager::clean(const std::string& name)
//{
//	auto it = assets.find(name);
//	if (it == assets.end())
//		throw std::exception(("can't clean " + name + " from assets").c_str());
//
//	delete it->second;
//}
