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
#include "FileManager.h"
#include <algorithm>
#include <Windows.h>

FileManager::FileManager(AHKHandler handler, int player)
{
	ahk = handler;
	playerNum = player;

	std::string result;
	//ifstream* in = new std::ifstream(LOCATION_DATA, std::ifstream::in);
}

void FileManager::SendFile(std::wstring fileName)
{
	cout << "encoding" << endl;
	wstring wFile = L"python \"C://0adProcessor/Encoder/encoder.py\" \"0\" \"" + fileName + L"\"";
	LPWSTR file = (LPWSTR)wFile.c_str();
	//ahk.RunScriptWithParameters(file);

	wstring wencoded_filename = fileName + L"-encoded";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	string encoded_filename = converter.to_bytes(wencoded_filename);
	fileIn = new std::ifstream(encoded_filename, std::ifstream::in | std::ifstream::binary);
	Move move;
	std::string buffer;
	while(std::getline(*fileIn, buffer))
	{
		if(buffer == "\r")
			continue;
		int j = 0;
		for(int i = 0; i < NUM_BUILDINGS; i++)
		{
			if(buffer.substr(i, 1) == "1")
			{
				move.units[j++] = i;
			}
		}
		move = ShuffleMove(move);
		ahk.SendMove(move);
		move = *(new Move);
	}
}

void FileManager::ReadMoves(wstring log_location)
{
	fileIn = new std::ifstream(log_location, std::ifstream::in | std::ifstream::binary);
	std::string buffer;

	fileOut = new std::ofstream(WRITE_FILE, std::ofstream::out | std::ofstream::binary);
	while(std::getline(*fileIn, buffer))
	{
		if(buffer.substr(0,3) == "cmd")
		{
			char p_num = buffer[4];
			//If it wasn't me that sent it:
			if(atoi(&p_num) != playerNum)
			{
				string units_s;
				int i = 0;
				for(; buffer[i] != '['; i++)
				{
				}
				int begin = ++i;
				for(;buffer[i] != ']'; i++)
				{
				}
				int end = i;

				//Get the unit ids from the commands
				units_s = buffer.substr(begin, end-begin);
				vector<string> units = split(units_s, ',');
				vector<int> units_i = vector<int>(units.size());
				for(int i = 0; i < units.size(); i++)
				{
					units_i[i] = atoi(units[i].c_str());
				}

				//Adjust for unit id offsets
				if(p_num == '1')
				{
					for(int i = 0; i < units.size(); i++)
					{
						units_i[i] -= PLAYER_ONE_OFFSET;
					}
				}
				else if(p_num == '2')
				{
					for(int i = 0; i < units.size(); i++)
					{
						units_i[i] -= PLAYER_TWO_OFFSET;
					}
				}

				char bitstring[NUM_BUILDINGS + 1];
				//zero out the bitstring
				for(int i = 0; i < NUM_BUILDINGS; i++)
				{
					bitstring[i] = '0';
				}
				bitstring[NUM_BUILDINGS] = '\0';

				for(int i = 0, j = 0; i < units_i.size() && j < 1600; j++)
				{
					if(j == units_i[i])
					{
						bitstring[j] = '1';
						i++;
					}
				}
				*fileOut << bitstring;
				*fileOut << endl;
			}
		}
	}

	fileOut->flush();

	

	wstring wFile = L"python \"C://0adProcessor/Encoder/encoder.py\" \"1\" \"" + WRITE_FILE + L"\"";
	LPWSTR file = (LPWSTR)wFile.c_str();
	ahk.RunScriptWithParameters(file);


	/*
	while(messagesToReceive > 0)
	{
		std::string line;
		getline(*moveIn, line);

		std::string units, x, z, xz;
		int index = 0;
		char cPlayerNum;
		//_itoa_s(playerNum, &cPlayerNum, 2, 10);
		//line[index] == cPlayerNum &&
		if(line.length() > 0)
		{
			Move move;
			move.atk = false;
			uint128_t data;
			
			data.a = 0x0001FFFFFFFFFFFF;
			data.b = 0xFFFFFFFFFFFF1000;

			while(line[index] != ':') index++;
			int typeColon = index;
			while(line[index] != '[') index++;
			int leftB = index;
			while(line[index] != ']') index++;
			int rightB = index;
			while(line[index] != ':') index++;
			int xColon = index;
			while(line[index] != ',') index++;
			int xComma = index;
			while(line[index] != ':') index++;
			int zColon = index;
			while(line[index] != ',') index++;
			int zComma = index;

			units = line.substr(leftB+1, rightB - leftB - 1);
			x = line.substr(xColon+1, xComma - xColon - 1);
			z = line.substr(zColon+1, zComma - zColon - 1);

			if(!line[typeColon + 2] == 'w')
				move.atk = true;

			xz = x + "|" + z;

			move.location = locations[xz];
			//Off by one indexing
			move.location++;
			move.leftUnits = 0x0001FFFFFFFFFFFF;
			move.rightUnits = 0x00001FFFFFFFFFFF;

			std::vector<std::string> unitV = split(units, ',');

			for(int i = 0; i < unitV.size(); i++)
			{
				//The power of two is equal to the unit tag minus the first unit tag
				//TODO check player two unit tags
				int power;
				if(playerNum == HOST)
					power = atoi(&unitV[i][0]) - 139;
				else
					power = atoi(&unitV[i][0]) - 139;

				if(power < 0)
					continue;


				if(power < 45)
				{
					move.rightUnits ^= (ONE <<(power));
					data.b ^= (ONE <<(power + 19));
				}
				else
				{
					move.leftUnits ^= (ONE <<(power - 45));
					data.a ^= (ONE <<(power - 45));
				}
			}

			uint128_t result = ahk.DecodeMove(move);

			char output[MESSAGE_SIZE];

			for(int i = 0; i < MESSAGE_SIZE; i++)
			{
				if (i < 8)
				{
					output[i] = ((result.b << (56 - i*8)) >> 56);
				}
				else
				{
					output[i] = ((result.a << (56 - (i-8)*8)) >> 56);
				}

			}
			
			for(int i = MESSAGE_SIZE - 1; i >= 0; i--)
			{
				fileOut->write(&output[i], 1);
			}
			fileOut->flush();
			messagesToReceive--;
		}
	}
	*/
}

bool FileManager::fileExists(std::string location)
{
	ifstream check(location);
	if(check.fail())
		return false;
	else return true;
}

Move FileManager::ShuffleMove(Move move)
{
	Move ret;
	ret.location = move.location;
	int first_empty = 200;
	for(int i = 0; i < 200; i++)
	{
		if(first_empty == 200 && move.units[i] < 0)
			first_empty = i;
		ret.units[i] = move.units[i];
	}

	bool odd = first_empty % 2 == 1;
	
	if(odd)
	{
		for(int i = 0; i < first_empty; i++)
		{
			ret.units[(i * 2) % first_empty] = move.units[i];
		}
	}
	else
	{
		for(int i = 0; i < first_empty; i++)
		{
			if(i < first_empty/2)
			{
				ret.units[(i * 2) % first_empty] = move.units[i];
			}
			else
			{
				ret.units[(i * 2 + 1) % first_empty] = move.units[i];
			}
		}
	}



	return ret;
}