#pragma once

#include <cstdint>
#include <map>
#include "AHKHandler.h"

struct loc
{
	string x, z;
};

//Player 1's first building has the id of PLAYER_ONE_OFFSET + 1
const int PLAYER_ONE_OFFSET = 40;
//Player 2's first building has the id of PLAYER_TWO_OFFSET + 1
const int PLAYER_TWO_OFFSET = 1640;

const wstring WRITE_FILE = L"C://0adProcessor/Output/Out";

class FileManager {
public:
	FileManager(AHKHandler handler, int playerNum);
	void SendFile(std::wstring fileName);
	void ReadMoves(wstring log_location);
	bool fileExists(std::string location);
private:
	AHKHandler ahk;
	WSADATA wsaData;
	int playerNum;
	std::istream* fileIn;
	std::ostream* fileOut;
	map<std::string, int> locations;
	Move ShuffleMove(Move move);
	/*SOCKET ConnectSocket;
	void InitializeSocket();
	bool CheckSocket();*/
};