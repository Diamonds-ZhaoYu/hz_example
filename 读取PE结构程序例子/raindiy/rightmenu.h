#ifndef _MAIN_H_3
#define _MAIN_H_3
#include <windows.h>
VOID CallUndll(HWND hWnd);
VOID CallCopyRow(HWND hWnd); //����listbox
VOID CallCopyAllRow(HWND hWnd); //����ȫ��listbox
VOID CallCopyById(HWND hWnd,int id); //����listview
VOID CallCopyByRow(HWND hWnd);   //����listview
VOID CallCopyByAllRow(HWND hWnd);   //����ȫ��listview
#endif