#include "pch.h"
#include "NetworkConfig.h"

NetworkConfig::NetworkConfig()
{
	tcp_port = 7385;
	udp_port = 7386;
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

	if (doc["tcp_port"].IsNumber())
		tcp_port = doc["tcp_port"].GetUint();

	if (doc["udp_port"].IsNumber())
		udp_port = doc["udp_port"].GetUint();
}

void NetworkConfig::saveDefaultConfigToFile(const fs::path& dir)
{
	json::Document doc;
	doc.SetObject();

	auto& allocator = doc.GetAllocator();

	json::Value arr(json::kArrayType);


	

	std::ofstream file(dir);

	if (!file)
		throw std::exception(("can't write " + dir.string()).c_str());

	json::OStreamWrapper osw = file;
	json::PrettyWriter<json::OStreamWrapper> writer(osw);

	doc.Accept(writer);
}
