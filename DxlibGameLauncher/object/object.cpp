#include "object.hpp"


object::Object::Object(std::wstring name, int graphHandle, Position position, Size size)
{
	isValid = true;
	this->name = name;
	this->graphHandle = graphHandle;
	this->position = position;
	this->size = size;
}

void object::Object::draw()
{
	DrawExtendGraph(position.x, position.y, position.x + size.width, position.y + size.height, graphHandle, true);
}

bool object::Object::isCursorOnObject(Position cursorPosition)
{
	return (cursorPosition.x >= position.x && cursorPosition.x < position.x + size.width)
		&& (cursorPosition.y >= position.y && cursorPosition.y < position.y + size.height);
}
