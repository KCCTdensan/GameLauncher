#pragma once
#include <string>

struct PlayData {
	int handle;
	std::string title;
	std::string author;

	PlayData() : handle(-1) {}
};