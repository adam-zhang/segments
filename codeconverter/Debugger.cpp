#include "stdafx.h"
#include "Debugger.h"
#include "CodeConverter.h"
#include <windows.h>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

string modulePath()
{
	vector<char> buffer(MAX_PATH);
	GetModuleFileNameA(AfxGetInstanceHandle(), &buffer[0], MAX_PATH);
	string path(&buffer[0]);
	return path.substr(0, path.rfind('\\') + 1);
}

void Debugger::writeFile(const string& text)
{
	try
	{
		auto fileName = "c:\\output.txt"; //modulePath() + "output.txt";
		fstream file(fileName, ios::out|ios::app);
		if (file.good())
		{
			file << text;
		}
		else
			write("can not open file");
	}
	catch(std::exception& e)
	{
		write(e.what());
	}
}

string dateTime()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	stringstream ss;
	ss << time.wYear << "-" << time.wMonth << "-" << time.wDay
		<< " " << time.wHour << ":" << time.wMinute << ":" << time.wSecond
		<< "." << time.wMilliseconds;
	return ss.str();
}

void Debugger::write(const std::string& notice)
{
	auto out = dateTime() + " " + notice + "\n";
	//writeFile(out);
	OutputDebugStringA(out.c_str());
	//MessageBoxA(NULL, notice, "", 0);
}

//void Debugger::write(const std::string& notice, size_t value)
//{
//	std::stringstream ss;
//	ss << notice << ":" << value;
//	write(ss.str());
//}


void Debugger::write(const std::string& notice, const std::string& value)
{
	std::stringstream ss;
	ss << notice << ":" << value;
	write(ss.str());
}


void Debugger::write(const std::wstring& notice)
{
	//MessageBox(NULL, notice.c_str(), TEXT(""), 0);
	write(CodeConverter::Utf16ToAnsi(notice));
}