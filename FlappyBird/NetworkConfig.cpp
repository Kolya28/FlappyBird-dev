#include "pch.h"
#include "NetworkConfig.h"

NetworkConfig::NetworkConfig()
{
	tcp_port = 7385;
	udp_port = 7386;
	default_hostnames = { "london.mykeenetic.ru" };
}

NetworkConfig::~NetworkConfig()
{
}

void NetworkConfig::loadFromFile(const fs::path& dir)
{
	std::ifstream file(dir);

	if (!file)
	{
		file.close();
		throw std::exception(("can't read " + dir.string()).c_str());
	}

	json::IStreamWrapper isw = file;
	json::Document doc;

	doc.ParseStream(isw);
	file.close();

	if (!doc.IsObject() || doc.HasParseError())
	{
		saveDefaultConfigToFile(dir);
		return;
	}

	if (doc["hostnames"].IsArray())
		for (auto& h : doc["hostnames"].GetArray())
		{
			if (h.IsString())
				hostnames.emplace_back(h.GetString());
		}

	if (doc["tcp_port"].IsNumber())
		tcp_port = doc["tcp_port"].GetUint();

	if (doc["udp_port"].IsNumber())
		udp_port = doc["udp_port"].GetUint();

	if (hostnames.empty())
		hostnames = std::move(default_hostnames);
}

void NetworkConfig::saveDefaultConfigToFile(const fs::path& dir)
{
	json::Document doc;
	doc.SetObject();

	auto& allocator = doc.GetAllocator();

	json::Value arr(json::kArrayType);


	for (auto& s : default_hostnames)
		arr.PushBack(json::StringRef(s.c_str()), allocator);

	doc.AddMember("hostnames", arr, allocator);

	std::ofstream file(dir);

	if (!file)
		throw std::exception(("can't write " + dir.string()).c_str());

	json::OStreamWrapper osw = file;
	json::PrettyWriter<json::OStreamWrapper> writer(osw);

	doc.Accept(writer);
}
