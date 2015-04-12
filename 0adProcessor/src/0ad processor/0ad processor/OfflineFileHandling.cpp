#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "OfflineFileHandling.h"

using namespace std;

void OfflineFileHandling::OfflineFiles()
{
	std::ostream* o_stream;
	std::istream* i_stream;

	_mkdir("C:\\0adProcessor");

	std::wstring ipath = L"C:\\0adProcessor/commands.txt";

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::stringstream ss;
	ss << time(NULL);
	std::wstring time_now = converter.from_bytes(ss.str());

	std::wstring opath = L"C:\\0adProcessor/fixedCommands " + time_now + L".txt";

	i_stream = new std::ifstream(ipath, std::ifstream::in);
	o_stream = new std::ofstream(opath, std::ofstream::out | std::ofstream::trunc);

	

	std::string result;
	std::string units, xStr, zStr;
	std::vector<std::string> bracketSplit, colonSplit;


	//There is some complicated string splitting going on here
	//The format of the input is as follows (Things in all caps are variable):
	//turn TURN_NUM cmd CMD_NUM {"type":"walk","entities":[UNIT_LIST],"x":X_COORD,"z":Z_COORD,"queued":false}
	//
	//We extract UNIT_LIST, X_COORD, and Z_COORD by splitting repeatedly:
	//Split on ']'
	//0:
	//	Split on '['
	//	1:
	//		save as list of units
	//1:
	//	Split on ':'
	//	1:
	//		split on ','
	//		0:
	//			save as x
	//	2:
	//		split on ','
	//		0:
	//			save as z


	while(getline(*i_stream, result))
	{
		bracketSplit = split(result, ']');

		units = split(bracketSplit[0], '[')[1];
		
		colonSplit = split(bracketSplit[1], ':');

		xStr = split(colonSplit[1], ',')[0];
		zStr = split(colonSplit[2], ',')[0];


		*o_stream << units << "|" << xStr << "|" << zStr << "\n";
	}
	
	o_stream->flush();

	//std::wstring path = psLogDir() / L"bridgar_test" / L"commands.txt";
	//CreateDirectories(path.Parent(), 0700);
	//i_Stream = new std::ofstream(OsString(path).c_str(), std::ofstream::out | std::ofstream::trunc);

}