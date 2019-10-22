#pragma once

#include "../size.hpp"
#include <string>
#include <DxLib.h>


namespace object
{
	class Graph
	{
		int handle;

	public:
		Graph(const Graph &) = delete;
		Graph &operator=(const Graph &) = delete;
		Graph(std::wstring filePath)
		{
			handle = LoadGraph(filePath.c_str());
		}
		~Graph()
		{
			DeleteGraph(handle);
		}
	};
}