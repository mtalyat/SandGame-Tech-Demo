#include "Event.h"

using namespace eng;

Event::Event()
{

}

void Event::addFunction(std::function<void()> func)
{
	functions.push_back(func);
}

void Event::invoke()
{
	for (int i = 0; i < functions.size(); i++)
	{
		functions[i]();
	}
}
