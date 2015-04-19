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

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>
#include <codecvt>
#include <time.h>
#include <sstream>
#include <Windows.h>
#include <strsafe.h>
#include <bitset>
#include <stdint.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
#include <math.h>

using namespace std;

// TODO: reference additional headers your program requires here

struct Move {
	uint32_t location;
	short units[200];
};

struct uint128_t {
	uint64_t a, b;
};

const int NUM_BUILDINGS = 800;
const int WIDTH = 950;
const int HEIGHT = 276;
const int HOST = 1;
const int GUEST = 2;
const int MESSAGE_SIZE = 14;
const uint64_t ONE = 0x0000000000000001;
const std::wstring LOCATION_DATA = L"C:/0adProcessor/950x276Locations.txt";
//const std::wstring MOVE_EXECUTABLE = L"\"C:/Users/Bridgar/Documents/0 ad pluggable/0-ad-pluggable-transport/Scripts/SendMove.exe\"";
//const std::wstring END_EXECUTABLE = L"\"C:/Users/Bridgar/Documents/0 ad pluggable/0-ad-pluggable-transport/Scripts/ExitGame.exe\"";
//const std::wstring MOVE_RECEIVING = L"C:/Users/Bridgar/AppData/Local/0ad/logs/bridgar_test/commands.txt";
//const std::wstring FILE_OUTPUT = L"C:/0adProcessor/DataOut.txt";

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);