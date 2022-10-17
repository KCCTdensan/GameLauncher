#pragma once
#include <string>

struct PlayData {
	int handle;
	std::string title;
	std::string author;

	PlayData() : handle(-1) {}
	PlayData(std::string _title, std::string _author) : handle(-1), title(_title), author(_author) {}
};