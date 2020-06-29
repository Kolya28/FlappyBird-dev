#include "pch.h"
#include "ServerThread.h"

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	ServerThread server;

	server.init(fs::current_path());
	server.run();
	server.cleanup();
}