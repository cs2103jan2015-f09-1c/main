//@author A0113736J-reused
#pragma once
#include <windows.h>

class Color{
public:
    enum ColorList{
		BLACK, BLUE, GREEN, CYAN, RED, MAGENTA,
		BROWN, LIGHTGREY, DARKGREY, LIGHTBLUE, LIGHTGREEN,
		LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE,
		BLINK
	};
	Color(void);
    ~Color(void);

	static void TextColor(int fontcolor,int backgroundcolor,HANDLE 	hStdOut);
	static HANDLE hStdOut;

private:
	int textColor;
	int textBackground;
};