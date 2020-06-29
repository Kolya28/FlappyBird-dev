#pragma once
class Connection
{
public:
	Connection();
	~Connection();
	//void setThread(std::thread* thread);
	bool sendToken(SOCKET s, SOCKADDR_IN& addr);
	bool waitToken();
	bool notify(SOCKET tcp);
	//void handler();
	static bool checkToken(const std::string& token, SOCKET s);

	static SOCKET udp;
private:
	SOCKADDR_IN client_addr;

	std::thread* player_thread;

	std::mutex mtx_tcp;
	SOCKET tcp = INVALID_SOCKET;

	std::string token;
	std::map<std::string, Connection*>::iterator it_token;

	static int sizeof_addr;
	static int send_count;
	static std::atomic<size_t> count;

	

	static std::mutex mtx_tokens;
	static std::map<std::string, Connection*> tokens;

	std::mutex mtx_wait_token;
	std::condition_variable cv_token;
};

