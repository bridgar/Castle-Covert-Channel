//	Castle is a covert channel for use with 0 A.D.
//    Copyright (C) 2015  Bridger Hahn
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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