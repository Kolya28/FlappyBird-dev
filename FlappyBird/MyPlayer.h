#pragma once
#include "pch.h"
class MyPlayer
{
	friend class StatesManager;
public:
	
	std::string nick;

	void saveToFile(const fs::path& dir)
	{
		std::ofstream file(dir);

		if (!file)
			throw std::exception("can't write player.json");

		json::Document doc;

		doc.SetObject();
		auto& allocator = doc.GetAllocator();

		doc.AddMember("nick", json::StringRef(nick.c_str()), allocator);

		json::OStreamWrapper osw = file;
		json::PrettyWriter<json::OStreamWrapper> writer(osw);
		doc.Accept(writer);
	}

private:
	MyPlayer()
	{
		nick = "Player";
	}

	void readFromFile(const fs::path& dir)
	{
		json::Document doc;

		std::fstream file(dir);
		if (!file)
			throw std::exception("can't open player.json");

		json::IStreamWrapper isw = file;
		doc.ParseStream(isw);

		if (!doc.IsObject() || doc.HasParseError())
		{
			saveDefaultToFile(dir);
			return;
		}

		if (doc["nick"].IsString())
			nick = doc["nick"].GetString();
	}

	void saveDefaultToFile(const fs::path& dir)
	{
		std::ofstream file(dir);

		if (!file)
			throw std::exception("can't write player.json");

		json::Document doc;

		doc.SetObject();
		auto& allocator = doc.GetAllocator();

		doc.AddMember("nick", "Player", allocator);

		json::OStreamWrapper osw = file;
		json::PrettyWriter<json::OStreamWrapper> writer(osw);
		doc.Accept(writer);
	}

	
};

