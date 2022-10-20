#pragma once
#include <string>

class StringConvert {
public:
	std::wstring ConvertString(const std::string& input)
	{
		size_t i;
		wchar_t* buffer = new wchar_t[input.size() + 1];
		mbstowcs_s(&i, buffer, input.size() + 1, input.c_str(), _TRUNCATE);
		std::wstring result = buffer;
		delete[] buffer;
		return result;
	}
	std::string ConvertString(const std::wstring& input)
	{
		size_t i;
		char* buffer = new char[input.size() * MB_CUR_MAX + 1];
		wcstombs_s(&i, buffer, input.size() * MB_CUR_MAX + 1, input.c_str(), _TRUNCATE);
		std::string result = buffer;
		delete[] buffer;
		return result;
	}
};