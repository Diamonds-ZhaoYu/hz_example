// example1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include "conio.h"	
#include <Windows.h>	//windows api ͷ

//ö���ִ���
BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam) 
{ 

    int i, idChild; 
    idChild = ::GetWindowLong(hwndChild, GWL_ID);
	printf("�Ӵ��ھ����0x%x ,idChild: %d \n",hwndChild,idChild);
	
	::ShowWindow(hwndChild,SW_HIDE);

    return TRUE;
}



int main(int argc, _TCHAR* argv[])
{
	//���Ҵ��ھ��
	HWND hWnd = ::FindWindow(NULL,_TEXT("������"));
	
	if (hWnd != 0) 
	{
		printf("�����ھ��: 0x%x \n",hWnd);

		//ö���ִ���
		EnumChildWindows(hWnd, EnumChildProc, NULL); 

		//::CloseWindow(hWnd);
	} else {
		printf("û���ҵ����ھ��\n");
	}
	

	getchar();
	return 0;
}

