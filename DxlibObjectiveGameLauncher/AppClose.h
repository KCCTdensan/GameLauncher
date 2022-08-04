#pragma once
class AppClose
{
public:
	static void Close();
	static bool GetClosed() { return closed; }

private:
	static bool closed;
};

