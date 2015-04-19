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

#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "AHKHandler.h"

void AHKHandler::SendMove(Move move)
{
	std::wstring temp = MOVE_EXECUTABLE;
	temp += L" \"";
	for(int i = 0; i < 200; i++)
	{
		int x = 51 + ((int)(move.units[i] / 32)) * 23.5;
			x -= move.units[i]%32 / 10;
		int z = 121 - 13.1875 + 13.1875 * (move.units[i] %32);
		if((move.units[i] / 32) > 24)
		{
			x = 920 + ((int)(move.units[i] / 32 - 25)) * 23.5;
			x += move.units[i]%32 / 10;
		}
		if(x < 20 || z < 100 || x > 1580 || z > 700)
		{
			temp += L"0\" \"0\" \"";
			
			continue;
		}
		temp += std::to_wstring(x) + L"\" \"";
		temp += std::to_wstring(z) + L"\" \"";
	}
	temp += L"775\" \"450\"";
	LPWSTR lpApplicationName = (LPWSTR)temp.c_str();

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	
	if(!CreateProcess(NULL,
				lpApplicationName,
				NULL,
				NULL,
				FALSE,
				NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE|CREATE_UNICODE_ENVIRONMENT,
				NULL,
				NULL,
				&si,
				&pi
	                  ))
	{
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		cout << "Failure";
		exit(0);
	}

	WaitForSingleObject(pi.hProcess,INFINITE);
}

void AHKHandler::EndGame()
{
	std::wstring temp = END_EXECUTABLE;

	LPWSTR lpApplicationName = (LPWSTR)temp.c_str();

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	
	if(!CreateProcess(NULL,
				lpApplicationName,
				NULL,
				NULL,
				FALSE,
				NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE|CREATE_UNICODE_ENVIRONMENT,
				NULL,
				NULL,
				&si,
				&pi
	                  ))
	{
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		cout << "Failure";
		exit(0);
	}

	WaitForSingleObject(pi.hProcess,INFINITE);
}

void AHKHandler::Launch0Ad()
{
	WCHAR ad0[MAX_PATH];
	//start with appdata
	wcscpy_s(ad0, appdata);
	//add default 0ad install directory
	wcscat_s(ad0, L"0 A.D. alpha\\binaries\\system\\pyrogenesis.exe");
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	
	if(!CreateProcess(ad0,
				NULL,
				NULL,
				NULL,
				FALSE,
				0,
				NULL,
				NULL,
				&si,
				&pi
	                  ))
	{
		printf( "CreateProcess failed (%d).\n", GetLastError() );
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		cout << "Failure";
		exit(0);
	}

	Sleep(3000);
}

void AHKHandler::StartAsHost()
{
	Launch0Ad();

	LPWSTR appName = (LPWSTR)L"C://0adProcessor/Scripts/Host.exe";

	RunScript(appName);
}

void AHKHandler::StartAsGuest(wstring ip)
{
	Launch0Ad();

	wstring app = (L"C://0adProcessor/Scripts/Guest.exe \"" + ip + L"\"");
	LPWSTR appName = (LPWSTR)app.c_str();

	RunScriptWithParameters(appName);
}

void AHKHandler::GameStart()
{
	wstring app = (L"C://0adProcessor/Scripts/Start.exe");
	LPWSTR appName = (LPWSTR)app.c_str();

	RunScript(appName);
}

void AHKHandler::RunScript(LPWSTR name)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	if(!CreateProcess(name,
				NULL,
				NULL,
				NULL,
				FALSE,
				0,
				NULL,
				NULL,
				&si,
				&pi
	                  ))
	{
		printf( "CreateProcess failed (%d).\n", GetLastError() );
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		cout << "Failure";
		exit(0);
	}
	WaitForSingleObject(pi.hProcess,INFINITE);
}

void AHKHandler::RunScriptWithParameters(LPWSTR name)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	if(!CreateProcess(NULL,
				name,
				NULL,
				NULL,
				FALSE,
				0,
				NULL,
				NULL,
				&si,
				&pi
	                  ))
	{
		printf( "CreateProcess failed (%d).\n", GetLastError() );
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		cout << "Failure";
		exit(0);
	}
	WaitForSingleObject(pi.hProcess,INFINITE);
}