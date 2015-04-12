// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

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