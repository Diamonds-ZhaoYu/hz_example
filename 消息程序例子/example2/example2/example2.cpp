// example2.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "example2.h"
#include "main.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	::DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, Main_Proc);
    return(0);
}




