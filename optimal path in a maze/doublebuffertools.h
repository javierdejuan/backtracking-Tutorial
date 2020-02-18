#pragma once
#ifndef double_buffer_tools_h
#define double_buffer_tools_h

#include"pch.h"
#define WIDTH 256
#define HEIGHT 120

int initializeConsole();
void writeLine(WCHAR buffline[WIDTH], const int line,const int len);
void fillchiBuffer();
int drawConsole();

#endif