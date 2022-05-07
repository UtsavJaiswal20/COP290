#include <iostream>
#include <WS2tcpip.h>

#include "SDL_mixer.h"
#include <string>

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

int main(int argc, char *argv[])
{

	string ipAddress = "192.168.121.191";
	int port = 54000;

	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	// Do-while loop to send and receive data
	char buf[4096];
	string userInput;
		
	int FPS = 50;
	int ftime = 1000 / FPS;

	Uint32 itime;
	Uint32 jtime;
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
		itime = SDL_GetTicks();
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
		if (currenttime < ftime) {
			SDL_Delay(ftime - currenttime);
		}


		jtime = SDL_GetTicks();
		if (Game::sscore >= 500) {
			Game::isRunning = false;
			cout << "> ";
			userInput = Game::player_name + (std::string)" Wins";
			cout << endl;
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					// Echo response to console
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}

		else if (jtime-itime >=1000)		// Make sure the user has typed in something
		{
			// Send the text
			cout << "> ";
			userInput = (std::string)"Client player " +  Game::player_name + (std::string)"'s score is " + std::to_string(Game::sscore);
			cout << endl;
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					// Echo response to console
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
			itime = jtime;
		}
	}

	start->clean();
	closesocket(sock);
	WSACleanup();
	

	return 0;
}