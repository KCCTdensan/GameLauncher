#pragma once
class MainThread
{
public:
	static bool SetEnd(bool _flag) { end = _flag; return true; }
	static bool SetEnd() { return end; }
private:
	static bool end;
};

