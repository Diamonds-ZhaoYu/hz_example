#ifndef _MAIN_H
#define _MAIN_H

DWORD WINAPI ThreadProc( LPVOID lpParameter);
DWORD WINAPI FuncProc( LPVOID lpParameter);
BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif
