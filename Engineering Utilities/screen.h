#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include <stack>
#include <locale>
#include <codecvt>

class screen
{
private:
	std::vector<HWND> windows;
	std::wstring text;
	inline static std::stack<screen*> prev;
	inline static screen* curr;
public:
	screen();
	screen(std::wstring);
	void push_back(HWND&);
	int size() const;
	HWND at(unsigned short) const;
	std::wstring getText() const;
	static void goBack(HWND&);
	static void goTo(screen*, HWND&);
	static screen* getCurr();
	static void setStart(screen*);
};