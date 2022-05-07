
#include <iostream>
#include <WS2tcpip.h>

#include "SDL_mixer.h"
#include <string>
#include <thread>

#pragma comment (lib, "ws2_32.lib")

#include "Menus/StartMenu.h"
#include "Game.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Menus/Instructions.h"

using namespace std;

Game* start;
StartMenu* smenu;
//Instructions* instrmenu;

void server() {
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return;
	}

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return;
	}

	//ip address and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));
	listen(listening, SOMAXCONN);
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<
			ntohs(client.sin_port) << endl;
	}

	closesocket(listening);

	char buf[4096];
	while (start->isrunning()) {
		ZeroMemory(buf, 4096);

		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}

		if (bytesReceived == 0)
		{
			cout << "Client disconnected " << endl;

		}

		cout << string(buf, 0, bytesReceived) << endl;
		string input;
		input = (std::string)"Server player " + Game::player_name + (std::string)"'s score is " + std::to_string(Game::sscore);
		if (Game::sscore >= 500) {
			Game::isRunning = false;
			input = Game::player_name + (std::string)" Wins";
			break;
		}
		send(clientSocket, input.c_str(), input.size() + 1, 0);
	}

	start->clean();
	closesocket(clientSocket);

	WSACleanup();

	system("pause");
}

void Gamee() {
	int FPS = 50;
	int ftime = 1000 / FPS;

	Uint32 starttime;
	Uint32 currenttime;



	start = new Game();

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	Game::music = Mix_LoadWAV("Resources/Audiosample1.wav");
	Mix_PlayChannel(-1, Game::music, -1);

	start->initialize("Window", 1000, 800, false);
	//std::cout << "1" << std::endl;

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Resources/Sample.ttf", 45);
	//std::cout << "1" << std::endl;

	smenu = new StartMenu();

	//std::cout << "1.1" << std::endl;
	int get = smenu->makemenu();
	//std::cout << "1.1" << std::endl;
	if (get == 1) {
		Game::isRunning = false;
	}

	//bool isbool = Game::isRunning;
	//start->clean();
	//start->initialize("Window", 1000, 800, false);
	//Game::isRunning = isbool;
	//std::cout << Game::player_name << std::endl;

	while (start->isrunning())
	{
		starttime = SDL_GetTicks();
		//std::cout << "here" << std::endl;
		start->handleEvents();
		//std::cout << "here1" << std::endl;
		start->update();
		//std::cout << "here2" << std::endl;
		start->render();
		currenttime = SDL_GetTicks() - starttime;
	}

}

int main(int argc, char* argv[])
{
	thread th1(Gamee);
	thread th2(server);
	th1.join();
	th2.join();
	return 0;
}