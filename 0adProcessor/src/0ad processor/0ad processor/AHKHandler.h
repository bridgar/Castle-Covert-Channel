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