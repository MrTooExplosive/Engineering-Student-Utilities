#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include <stack>

class screen
{
private:
	std::vector<HWND> windows;
	std::string text;
	inline static std::stack<screen*> prev;
	inline static screen* curr;
public:
	screen();
	screen(std::string);
	void push_back(HWND&);
	int size() const;
	HWND at(unsigned short) const;
	std::string getText() const;
	static void goBack();
	static void goTo(screen*);
	static screen* getCurr();
	static void setStart(screen*);
};