#include "pch.h"
#include "Connection.h"

std::atomic<size_t> Connection::count = 0;
int Connection::send_count = 5;

std::mutex Connection::mtx_tokens;
std::map<std::string, Connection*> Connection::tokens;

int Connection::sizeof_addr = sizeof(SOCKADDR_IN);
SOCKET Connection::udp = INVALID_SOCKET;


Connection::Connection()
{
	tcp = INVALID_SOCKET;
}

Connection::~Connection()
{
	mtx_tcp.lock();
	if (tcp > 0)
		closesocket(tcp);
	mtx_tcp.unlock();
}

bool Connection::sendToken(SOCKET s, SOCKADDR_IN& addr)
{
	client_addr = addr;

	if(token.empty())
		token = std::to_string(count++) + '_'
		+ std::to_string(rand()) + '_'
		+ VERSION;

	mtx_tokens.lock();
	auto it = tokens.emplace(token, this);
	mtx_tokens.unlock();


	
	if (!it.second)
		return false;

	it_token = it.first;

	for (int i = 0; i < send_count; i++)
		sendto(s, token.c_str(), token.size() + 1, NULL, (SOCKADDR*)&client_addr, sizeof(client_addr));
	

	return true;
}

bool Connection::waitToken()
{
	std::cout << "wait token " << token << std::endl;
	std::unique_lock ul(mtx_wait_token);
	
	cv_token.wait_for(ul, 2s);
	
	mtx_tokens.lock();

	tokens.erase(it_token);

	mtx_tokens.unlock();

	mtx_tcp.lock();
	if (tcp == INVALID_SOCKET)
	{
		tcp = 0;
		mtx_tcp.unlock();
		//std::cout << "old token " << token << std::endl;
		return false;
	}
	mtx_tcp.unlock();

	std::cout << "Connected\n";
	send(tcp, "OK", sizeof("OK"), NULL);

	return true;
}

bool Connection::notify(SOCKET tcp)
{
	mtx_tcp.lock();

	if (this->tcp == 0)
	{
		mtx_tcp.unlock();
		return false;
	}

	this->tcp = tcp;

	mtx_tcp.unlock();

	cv_token.notify_one();

	return true;
}

bool Connection::checkToken(const std::string& token, SOCKET s)
{
	mtx_tokens.lock();

	auto it = tokens.find(token);

	

	if (it == tokens.end())
	{
		mtx_tokens.unlock();
		return false;
	}

	

	Connection* p = it->second;
	mtx_tokens.unlock();
	

	return p->notify(s);
}

