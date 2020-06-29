#pragma once
#include "pch.h"

class NetworkConfig
{
public:
	NetworkConfig();
	~NetworkConfig();

	void loadFromFile(const fs::path& dir);

	std::vector<std::string> hostnames;
	u_short tcp_port, udp_port;
	
private:
	void saveDefaultConfigToFile(const fs::path& dir);
	std::vector<std::string> default_hostnames;
};

