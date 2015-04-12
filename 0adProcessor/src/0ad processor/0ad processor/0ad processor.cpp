// 0ad processor.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "AHKHandler.h"
#include "FileManager.h"
#include "Shlobj.h";
#include "FileAPI.h";

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	AHKHandler ahk;
	int playerNum;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	WCHAR appdata[MAX_PATH];
	WCHAR logs[MAX_PATH];
	WCHAR srch[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, appdata);
	//Change from roaming to local
	wcscat_s(appdata, L"\\..\\Local\\");
	//Give this to ahk
	wcscpy_s(ahk.appdata, appdata);
	wcscpy_s(logs, appdata);
	wcscat_s(logs, L"0ad\\logs\\sim_log\\");
	wcscpy_s(srch, logs);
	wcscat_s(srch, L"*");
	
	
	open_game:
	cout << "Would you like a game of 0 ad to be opened for you? (y/n)\n";
	char openGame;
	cin >> openGame;
	cout << "\n";

	//Initial setup checks
	if(openGame == 'y')
	{
		host_game:
		cout << "Would you like to host the game? (y/n)\n";
		char hostGame;
		cin >> hostGame;
		cout << "\n";

		if(hostGame == 'y')
		{
			playerNum = HOST;

			ahk.StartAsHost();

			cout << "Press any key when your guest has joined, you have started the game, and the load screen has finished.\n";
			char a;
			cin >> a;
			cout << "\n";
		}
		else if(hostGame == 'n')
		{
			playerNum = GUEST;
			cout << "Please enter the ip of the host.\n";
			std::string ip;
			cin >> ip;
			std::wstring wide = converter.from_bytes(ip);

			ahk.StartAsGuest(wide);

			cout << "Press any key when you have entered the lobby. \n";
			char a;
			cin >> a;
			cout << "\n";

			ahk.GameStart();

			cout << "Press any key when your host has started the game and the load screen has finished. \n";
			cin >> a;
			cout << "\n";
		}
		else
		{
			cout << "Please only enter 'y' or 'n'\n";
			goto host_game;
		}
	}
	else if(openGame == 'n')
	{
		custom_host:
		cout << "For the game that you have already made, are you the host?(y/n)\n";
		char isHost;
		cin >> isHost;
		cout << "\n";

		if(isHost == 'y')
		{
			playerNum = HOST;
		}
		else if(isHost == 'n')
		{
			playerNum = GUEST;
		}
		else
		{
			cout << "Please only enter 'y' or 'n'\n";
			goto custom_host;
		}
	}
	else
	{
		cout << "Please only enter 'y' or 'n'\n";
		goto open_game;
	}
	
	FileManager* fm = new FileManager(ahk, playerNum);

	//Main Castle Loop
	while(true)
	{
		main_loop:
		cout << "Type 's' to send a file or 'r' to reread the commands received so far or 'q' to quit Castle\n";
		char castle;
		cin >> castle;
		cout << "\n";
		if(castle == 's')
		{
			send_file:
			cout << "Please enter the location of the file that you would like to send.\n";
			string file_location;
			cin >> file_location;
			wstring wfile_location = converter.from_bytes(file_location);
			cout << "\n";
			if(fm->fileExists(file_location))
			{
				fm->SendFile(wfile_location);
			}
			else
			{
				cout << "The file given could not be found. Check that the file exists and is in an accessible directory.\n";
			}
			goto main_loop;
		}
		else if(castle == 'r')
		{
			WIN32_FIND_DATA most_recent, buffer;
			HANDLE search = FindFirstFile(srch, &most_recent);
			if(search == INVALID_HANDLE_VALUE)
			{
				cout << "No log files found. Please start a game.\n";
				goto main_loop;
			}
			while(FindNextFile(search, &buffer) != 0)
			{
				//Ignore the cases of "." and ".."
				if(most_recent.cFileName[0] == '.')
					most_recent = buffer;
				if(CompareFileTime(&buffer.ftLastAccessTime, &most_recent.ftLastAccessTime) == 1)
					most_recent = buffer;
			}
			FindClose(search);
			wcscat_s(logs, most_recent.cFileName);
			wcscat_s(logs, L"\\commands.txt");
			fm->ReadMoves(logs);
			cout << "The decoded moves are now in C://0adProcessor/Output/Out-decoded" << endl;
			goto main_loop;
		}
		else if(castle == 'q')
		{
			ahk.EndGame();
			return 0;
		}
		else
		{
			cout << "Please only enter 's' or 'r' or 'q'\n";
			goto main_loop;
		}
	}

    return 0 ;
}


