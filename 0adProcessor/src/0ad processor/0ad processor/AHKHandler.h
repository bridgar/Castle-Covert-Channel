#pragma once

#include <cstdint>

//00000000000000011111111111111111
const uint32_t LOCATION_MASK = 131071;
//00000111111111100000000000000000
const uint32_t UNITS_MASK =  134086656;

const std::wstring MOVE_EXECUTABLE = L"\"C://0adProcessor/Scripts/SendMove.exe\"";
const wstring END_EXECUTABLE = L"\"C://0adProcessor/Scripts/ExitGame.exe\"";

class AHKHandler {
public:
	void SendMove(Move move);
	uint128_t DecodeMove(Move move);
	Move EncodeMove(uint128_t data);
	void EndGame();
	void StartAsGuest(wstring ip);
	void StartAsHost();
	WCHAR appdata[MAX_PATH];
	void RunScript(LPWSTR name);
	void RunScriptWithParameters(LPWSTR name);
	void GameStart();
private:
	void Launch0Ad();
};