#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include "doublebuffertools.h"

#define step 5
HANDLE hStdout, hNewScreenBuffer, hNewScreenBuffer2;
SMALL_RECT srctWriteRect;
CHAR_INFO chiBuffer[WIDTH * HEIGHT];
WCHAR Buffer[WIDTH * HEIGHT];
COORD coordBufSize;
COORD coordBufCoord;

int initializeConsole()
{
	int retval = 0; 
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	coordBufSize.X = WIDTH;
	coordBufSize.Y = HEIGHT;

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	srctWriteRect.Left = srctWriteRect.Top = 0;
	srctWriteRect.Right = WIDTH - 1;
	srctWriteRect.Bottom = HEIGHT - 1;

	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		0,
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);                   // reserved; must be NULL 
	hNewScreenBuffer2 = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		0,
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);                   // reserved; must be NULL 
	if (hNewScreenBuffer2 == INVALID_HANDLE_VALUE ||
		hNewScreenBuffer == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		retval= 1;
	}

	SetConsoleTitle(L"Plz let me double buffering.");
	SetConsoleScreenBufferSize(hNewScreenBuffer, coordBufSize);
	SetConsoleWindowInfo(hNewScreenBuffer, TRUE, &srctWriteRect);
	SetConsoleScreenBufferSize(hNewScreenBuffer2, coordBufSize);
	SetConsoleWindowInfo(hNewScreenBuffer2, TRUE, &srctWriteRect);

	memset((void*)Buffer, 0, (size_t)(WIDTH*HEIGHT));

	return retval;
}

void writeLine(WCHAR buffline[WIDTH], const int line,const int len)
{
	for (int x = 0; x < WIDTH; ++x)
	{
		Buffer[x + WIDTH * line] = ' ';

	}
	for (int x = 0; x <len; ++x)
	{
		Buffer[x + WIDTH * line] = buffline[x];

	}
}
void fillchiBuffer()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (iswdigit(Buffer[x + WIDTH * y]))
			{
				chiBuffer[x + WIDTH * y].Attributes = FOREGROUND_RED;
			}
			else
			{
				chiBuffer[x + WIDTH * y].Attributes = FOREGROUND_GREEN;			
			}
			chiBuffer[x + WIDTH * y].Char.UnicodeChar = Buffer[x + WIDTH * y];

		}
	}

}
int drawConsole()
{
	static int i = 0;
	int retval = 0; 
	HANDLE curScreenBufferHandle;

	if (i % 2 == 0) {
		curScreenBufferHandle = hNewScreenBuffer;
	}
	else {
		curScreenBufferHandle = hNewScreenBuffer2;
	}

	// clear

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			chiBuffer[x + WIDTH * y].Char.UnicodeChar = ' ';
			chiBuffer[x + WIDTH * y].Attributes = BACKGROUND_BLUE;
		}
	}



	fillchiBuffer();


	BOOL fSuccess = WriteConsoleOutput(
		curScreenBufferHandle, // screen buffer to write to 
		chiBuffer,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&srctWriteRect);

	if (!SetConsoleActiveScreenBuffer(curScreenBufferHandle)) {
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		retval = 1;
	}

	Sleep((DWORD)(step / 60.0f * 1000.0f));

	i++;
	return retval; 
}

