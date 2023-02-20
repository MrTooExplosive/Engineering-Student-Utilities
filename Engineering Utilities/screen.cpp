#include "screen.h"

screen::screen()
{
	text = "";
}

screen::screen(std::string msg)
{
	text = msg;
}

void screen::push_back(HWND& wind)
{
	windows.push_back(wind);
}

int screen::size() const
{
	return windows.size();
}

HWND screen::at(unsigned short i) const
{
	return windows.at(i);
}

std::string screen::getText() const
{
	return text;
}

void screen::goBack()
{
	if (prev.empty())
		return;

	for (int i = 0; i < curr->size(); i++)
		ShowWindow(curr->at(i), SW_HIDE);
	for (int i = 0; i < prev.top()->size(); i++)
		ShowWindow(prev.top()->at(i), SW_SHOW);
	curr = prev.top();
	prev.pop();
}

void screen::goTo(screen* next)
{
	if (next == curr)
		return;

	prev.push(curr);
	for (int i = 0; i < curr->size(); i++)
		ShowWindow(curr->at(i), SW_HIDE);
	for (int i = 0; i < next->size(); i++)
		ShowWindow(next->at(i), SW_SHOW);
	curr = next;
}

screen* screen::getCurr()
{
	return curr;
}

void screen::setStart(screen* home)
{
	curr = home;
}