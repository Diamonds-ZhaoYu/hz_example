#ifndef _MAIN_H_2
#define _MAIN_H_2

#include <windows.h>
VOID EnumMyProcess(HWND hwnd,int type);
BOOL InsertDll(int pid,PTSTR szDllPath);
VOID OpenFileDlls(HWND hWnd,HINSTANCE hInst);
VOID ListProcessModules1(DWORD dwPID,HWND hwnd);
VOID InDll(HWND hwnd);
BOOL UnloadDll(DWORD dwPid, char *strDllName);
VOID GetProMoudle(HWND hwnd);			 //�������ģ��
int IsDLLInfo(HWND hWnd,char *szDll);   //�ж�DLL�Ƿ����
VOID ListAddOrSub(HWND hwnd);
BOOL EnumMyProcessCmp(HWND hwnd,char *file);
#endif