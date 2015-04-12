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