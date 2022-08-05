#pragma once
#include <string>
#include <rpc.h>
#include <rpcdce.h>

class UUIDGenerator
{
public:
	UUIDGenerator()
		: tGUID() {}
	~UUIDGenerator() {}

	std::string GetGUID();

private:
	std::string GuidToString(GUID* _GUID);

	GUID tGUID;
};

