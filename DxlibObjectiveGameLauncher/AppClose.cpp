#include "AppClose.h"

bool AppClose::closed = false;

void AppClose::Close()
{
	closed = true;
}
