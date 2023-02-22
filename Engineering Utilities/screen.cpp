#include "screen.h"

screen::screen()
{
	text = L"";
}

screen::screen(std::wstring msg)
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

std::wstring screen::getText() const
{
	return text;
}

void screen::goBack(HWND& hWnd)
{
	if (prev.empty())
		return;

	for (int i = 0; i < curr->size(); i++)
		ShowWindow(curr->at(i), SW_HIDE);
	for (int i = 0; i < prev.top()->size(); i++)
		ShowWindow(prev.top()->at(i), SW_SHOW);
	curr = prev.top();
	prev.pop();
	RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_INTERNALPAINT | RDW_UPDATENOW | RDW_ALLCHILDREN);
}

void screen::goTo(screen* next, HWND& hWnd)
{
	if (next == curr)
		return;

	prev.push(curr);
	for (int i = 0; i < curr->size(); i++)
		ShowWindow(curr->at(i), SW_HIDE);
	for (int i = 0; i < next->size(); i++)
		ShowWindow(next->at(i), SW_SHOW);
	curr = next;
	RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_INTERNALPAINT | RDW_UPDATENOW | RDW_ALLCHILDREN);
}

screen* screen::getCurr()
{
	return curr;
}

void screen::setStart(screen* home)
{
	curr = home;
}