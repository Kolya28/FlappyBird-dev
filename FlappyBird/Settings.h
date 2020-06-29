#pragma once
#include "pch.h"


class Settings
{
public:
	Settings()
	{
		fullscreen = true;
		vsync = true;
		scale = 0.;
		max_fps = GetDeviceCaps(hdc, VREFRESH);
		height = GetDeviceCaps(hdc, VERTRES);
		width = GetDeviceCaps(hdc, HORZRES);
		key_repeat = false;
	}

	~Settings()
	{
		ReleaseDC(hwnd, hdc);
	}

	void loadFromFile(const fs::path& dir)
	{
		std::ifstream file(dir);

		if (!file)
			throw std::runtime_error("can't read settings.json");

		json::Document doc;
		json::IStreamWrapper isw = file;

		
		doc.ParseStream(isw);
		file.close();

		if (!doc.IsObject() || doc.HasParseError())
		{
			saveDefaultToFile(dir);
			return;
		}


		if (doc["fullscreen"].IsBool())
			fullscreen = doc["fullscreen"].GetBool();

		if (doc["vsync"].IsBool())
			vsync = doc["vsync"].GetBool();

		if (doc["scale"].IsNumber())
			scale = doc["scale"].GetFloat();

		if (doc["max_fps"].IsNumber())
			max_fps = doc["max_fps"].GetInt();

		if (doc["height"].IsNumber())
			height = doc["height"].GetInt();

		if (doc["width"].IsNumber())
			width = doc["width"].GetInt();

		if (doc["key_repeat"].IsBool())
			key_repeat = doc["key_repeat"].GetBool();
	}

	void saveDefaultToFile(const fs::path& dir)
	{
		std::ofstream file(dir);

		if (!file)
			throw std::exception("can't write settings.json");

		json::Document doc;

		doc.SetObject();
		auto& allocator = doc.GetAllocator();

		doc.AddMember("fullscreen", true, allocator);
		doc.AddMember("vsync", true, allocator);
		doc.AddMember("scale", json::Value(), allocator);
		doc.AddMember("max_fps", json::Value(), allocator);
		doc.AddMember("height", json::Value(), allocator);
		doc.AddMember("width", json::Value(), allocator);
		doc.AddMember("key_repeat", false, allocator);

		json::OStreamWrapper osw = file;
		json::PrettyWriter<json::OStreamWrapper> writer(osw);
		doc.Accept(writer);
	}

	bool fullscreen;
	bool vsync;
	float scale;
	int max_fps;
	int height;
	int width;

	bool key_repeat;
	
private:
	HWND hwnd = GetDesktopWindow();
	HDC  hdc = GetDC(hwnd);
};

